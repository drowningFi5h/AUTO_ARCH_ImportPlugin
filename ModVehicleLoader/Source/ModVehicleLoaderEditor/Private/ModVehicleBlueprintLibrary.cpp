#include "ModVehicleBlueprintLibrary.h"
#include "Misc/MessageDialog.h"

#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/Blueprint.h"
#include "Components/StaticMeshComponent.h"
#include "Factories/BlueprintFactory.h"
#include "AssetToolsModule.h"

#include "Engine/SimpleConstructionScript.h"
#include "Engine/SCS_Node.h"

#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "Factories/FbxFactory.h"
#include "Factories/FbxImportUI.h"
#include "Factories/FbxStaticMeshImportData.h"
#include "AutomatedAssetImportData.h"
#include "Framework/Application/SlateApplication.h"

#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformProcess.h"
#include "FileHelpers.h"

// =====================================================================
// SUPPORTING FUNCTIONS

static UMaterialInterface* FindMasterMaterial(const FString& SlotName)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FAssetData> AssetData;
    
    FARFilter Filter;
    Filter.ClassPaths.Add(UMaterial::StaticClass()->GetClassPathName());
    Filter.ClassPaths.Add(UMaterialInstanceConstant::StaticClass()->GetClassPathName());
    Filter.bRecursivePaths = true;
    Filter.PackagePaths.Add("/Game"); 

    AssetRegistryModule.Get().GetAssets(Filter, AssetData);

    UMaterialInterface* BestMatch = nullptr;

    for (const FAssetData& Data : AssetData)
    {
        FString PkgName = Data.PackageName.ToString();

        if (PkgName.Contains(TEXT("/CarImports/"), ESearchCase::IgnoreCase)) continue;

        if (Data.AssetName.ToString().Contains(SlotName, ESearchCase::IgnoreCase))
        {
            BestMatch = Cast<UMaterialInterface>(Data.GetAsset());
            if (PkgName.Contains(TEXT("/AUTO_MATERIALS/"), ESearchCase::IgnoreCase))
            {
                return BestMatch;
            }
        }
    }
    return BestMatch;
}

static void AutoMatchMaterials(UStaticMesh* Mesh)
{
    TArray<FStaticMaterial>& StaticMaterials = Mesh->GetStaticMaterials();

    for (int32 i = 0; i < StaticMaterials.Num(); i++)
    {
        FStaticMaterial& MatSlot = StaticMaterials[i];
        FString ImportedMatName = MatSlot.MaterialSlotName.ToString();

        UMaterialInterface* FoundMat = FindMasterMaterial(ImportedMatName);

        if (FoundMat)
        {
            UE_LOG(LogTemp, Warning, TEXT("MATCHED: Slot '%s' -> Asset '%s'"), *ImportedMatName, *FoundMat->GetName());
            MatSlot.MaterialInterface = FoundMat;
        }
    }

    Mesh->PostEditChange();
    Mesh->MarkPackageDirty();
}

static void CreateCompositeVehicleBlueprint(const TArray<UStaticMesh*>& Meshes)
{
    if (Meshes.Num() == 0) return;

    FString MainName = Meshes[0]->GetName();
    FString BPName = FString::Printf(TEXT("BP_%s_Composite"), *MainName);
    FString PackagePath = TEXT("/Game/CarImports/Blueprints");
    FString FullPath = FString::Printf(TEXT("%s/%s"), *PackagePath, *BPName);

    UPackage* Package = CreatePackage(*FullPath);
    
    UBlueprintFactory* Factory = NewObject<UBlueprintFactory>();
    Factory->ParentClass = AActor::StaticClass(); 

    UBlueprint* NewBP = Cast<UBlueprint>(Factory->FactoryCreateNew(
        UBlueprint::StaticClass(),
        Package,
        FName(*BPName),
        RF_Public | RF_Standalone,
        NULL,
        GWarn
    ));

    if (NewBP)
    {
        UE_LOG(LogTemp, Warning, TEXT("Creating Composite Blueprint with Physics Root: %s"), *BPName);

        USCS_Node* RootNode = nullptr;

        for (int32 i = 0; i < Meshes.Num(); i++)
        {
            UStaticMesh* Mesh = Meshes[i];
            
            FString CompName = (i == 0) ? TEXT("Body_Root") : FString::Printf(TEXT("Comp_%s"), *Mesh->GetName());
            
            USCS_Node* MeshNode = NewBP->SimpleConstructionScript->CreateNode(UStaticMeshComponent::StaticClass(), FName(*CompName));
            UStaticMeshComponent* ComponentTemplate = Cast<UStaticMeshComponent>(MeshNode->ComponentTemplate);
            
            ComponentTemplate->SetStaticMesh(Mesh);
            
            // --- PHYSICS & SCALE LOGIC ---
            if (i == 0)
            {
                // ROOT: Has Physics, Collision, and 1.1 Scale
                ComponentTemplate->SetCollisionProfileName(FName("BlockAllDynamic"));
                ComponentTemplate->SetSimulatePhysics(true);
                ComponentTemplate->SetMassOverrideInKg(NAME_None, 1500.0f, true);
                ComponentTemplate->SetWorldScale3D(FVector(1.1f)); 
                
                NewBP->SimpleConstructionScript->AddNode(MeshNode);
                RootNode = MeshNode; 
            }
            else
            {
                // OTHERS: No Physics, No Collision, 1.0 Scale
                ComponentTemplate->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
                ComponentTemplate->SetSimulatePhysics(false);
                ComponentTemplate->SetWorldScale3D(FVector(1.0f)); 
                
                NewBP->SimpleConstructionScript->AddNode(MeshNode);
                if (RootNode)
                {
                    MeshNode->SetParent(RootNode);
                }
            }
        }

        FKismetEditorUtilities::CompileBlueprint(NewBP);
        FAssetRegistryModule::AssetCreated(NewBP);
        Package->SetDirtyFlag(true);
        
        UE_LOG(LogTemp, Warning, TEXT("SUCCESS: Created Composite Blueprint at %s"), *FullPath);
    }
}

static void ProcessAssets(const TArray<UObject*>& ImportedAssets)
{
    TArray<UStaticMesh*> MeshesToProcess;

    for (UObject* Asset : ImportedAssets)
    {
        if (UStaticMesh* Mesh = Cast<UStaticMesh>(Asset))
        {
            AutoMatchMaterials(Mesh);
            MeshesToProcess.Add(Mesh);
        }
    }
    CreateCompositeVehicleBlueprint(MeshesToProcess);
}

static void ScanTempFolderForMeshes(TArray<UObject*>& OutAssets)
{
    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FString> ScanPaths;
    ScanPaths.Add(TEXT("/Game/CarImports/Temp"));
    AssetRegistryModule.Get().ScanPathsSynchronous(ScanPaths, true);

    TArray<FAssetData> AssetData;
    AssetRegistryModule.Get().GetAssetsByPath(FName("/Game/CarImports/Temp"), AssetData, true);

    for (const FAssetData& Data : AssetData)
    {
        if (Data.AssetClassPath.GetAssetName() == FName("StaticMesh"))
        {
            if (UObject* LoadedAsset = Data.GetAsset())
            {
                OutAssets.Add(LoadedAsset);
            }
        }
    }
}
// =====================================================================
// UModVehicleBlueprintLibrary IMPLEMENTATION

void UModVehicleBlueprintLibrary::OpenModFileDialog(FString& OutFilePath, bool& bSuccess)
{
    bSuccess = false;

    if (!FModuleManager::Get().IsModuleLoaded("DesktopPlatform")) 
    {
        FModuleManager::Get().LoadModule("DesktopPlatform");
    }

    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        TArray<FString> OpenFilenames;
        const void* ParentWindowHandle = nullptr;
        if (FSlateApplication::IsInitialized())
        {
            TSharedPtr<SWindow> ParentWindow = FSlateApplication::Get().GetActiveTopLevelWindow();
            if (ParentWindow.IsValid() && ParentWindow->GetNativeWindow().IsValid())
            {
                ParentWindowHandle = ParentWindow->GetNativeWindow()->GetOSWindowHandle();
            }
        }

        const bool bOpened = DesktopPlatform->OpenFileDialog(
            ParentWindowHandle,
            TEXT("Select Vehicle FBX"),
            TEXT(""),
            TEXT(""),
            TEXT("FBX Files|*.fbx"),
            EFileDialogFlags::None,
            OpenFilenames
        );

        if (bOpened && OpenFilenames.Num() > 0)
        {
            OutFilePath = OpenFilenames[0];
            bSuccess = true;
        }
    }
}

void UModVehicleBlueprintLibrary::ImportModVehicle(FString FilePath)
{
    UE_LOG(LogTemp, Log, TEXT("Blueprint Import Started: %s"), *FilePath);

    UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>();
    ImportData->bReplaceExisting = true;
    ImportData->DestinationPath = TEXT("/Game/CarImports/Temp");
    ImportData->Filenames.Add(FilePath);

    UFbxFactory* FbxFactory = NewObject<UFbxFactory>();
    ImportData->Factory = FbxFactory;
    
    FbxFactory->ImportUI = NewObject<UFbxImportUI>(FbxFactory);
    FbxFactory->ImportUI->MeshTypeToImport = FBXIT_StaticMesh;
    FbxFactory->ImportUI->bImportMaterials = true;
    FbxFactory->ImportUI->bImportTextures = true;
    FbxFactory->ImportUI->bImportMesh = true;
    // PIVOT FIX:
    FbxFactory->ImportUI->StaticMeshImportData->bTransformVertexToAbsolute = true; 
    FbxFactory->ImportUI->StaticMeshImportData->bBakePivotInVertex = false;

    FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
    TArray<UObject*> Assets = AssetToolsModule.Get().ImportAssetsAutomated(ImportData);

    if (Assets.Num() == 0)
    {
        ScanTempFolderForMeshes(Assets);
    }

    if (Assets.Num() > 0)
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Import Successful! Processing..."));
        ProcessAssets(Assets);
    }
    else
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Import Failed: No meshes found in Temp folder."));
    }
}

void UModVehicleBlueprintLibrary::PackModPlugin(FString PluginName)
{
    // --- SMART EXPORT with SELECTION ---
    IContentBrowserSingleton& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser").Get();
    TArray<FAssetData> Selection;
    ContentBrowser.GetSelectedAssets(Selection);
    
    if (Selection.Num() == 0)
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Please select the Vehicle Blueprint in the Content Browser first, then click Export!"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("--- STARTING SMART PACK FOR: %s ---"), *Selection[0].AssetName.ToString());

    FEditorFileUtils::SaveDirtyPackages(false, false, true, false, false, false);

    FString EngineDir = FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
    FString UnrealPakExe = EngineDir + TEXT("Binaries/Win64/UnrealPak.exe");
    FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    FString OutputDir = FPaths::ProjectSavedDir() + TEXT("StagedMods/");
    
    FString PakName = Selection[0].AssetName.ToString() + TEXT(".pak");
    FString OutputPak = OutputDir + PakName;

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    PlatformFile.CreateDirectoryTree(*OutputDir);

    FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
    TArray<FName> Dependencies;
    AssetRegistryModule.Get().GetDependencies(Selection[0].PackageName, Dependencies, UE::AssetRegistry::EDependencyCategory::Package);
    Dependencies.Add(Selection[0].PackageName);

    FString ResponseContent;
    int32 FileCount = 0;

    for (const FName& DepPackage : Dependencies)
    {
        FString PkgNameStr = DepPackage.ToString();
        
        if (!PkgNameStr.StartsWith("/Game/CarImports")) continue;

        FString RelPath = PkgNameStr.Replace(TEXT("/Game/"), TEXT("Content/"));
        FString AbsPath = ProjectDir + RelPath + TEXT(".uasset");

        if (!PlatformFile.FileExists(*AbsPath))
        {
             AbsPath = ProjectDir + RelPath + TEXT(".umap");
             if (!PlatformFile.FileExists(*AbsPath)) continue;
        }

        FString MountPath = PkgNameStr.Replace(TEXT("/Game/"), TEXT("../../../Game/"));
        MountPath += TEXT(".uasset");

        UE_LOG(LogTemp, Warning, TEXT("Adding to PAK: %s"), *AbsPath);
        ResponseContent += FString::Printf(TEXT("\"%s\" \"%s\"\n"), *AbsPath, *MountPath);
        FileCount++;
    }

    if (FileCount == 0)
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Error: No valid assets found to pack."));
        return;
    }

    FString ResponseFilePath = OutputDir + TEXT("PakList.txt");
    FFileHelper::SaveStringToFile(ResponseContent, *ResponseFilePath);
    FString Params = FString::Printf(TEXT("\"%s\" -create=\"%s\""), *OutputPak, *ResponseFilePath);

    int32 ReturnCode = 0;
    FString Result;
    FPlatformProcess::ExecProcess(*UnrealPakExe, *Params, &ReturnCode, &Result, nullptr);

    if (ReturnCode == 0)
    {
        FString Msg = FString::Printf(TEXT("Export Success! Created %s with %d files."), *PakName, FileCount);
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(Msg));
        UE_LOG(LogTemp, Warning, TEXT("Pak Success: %s"), *OutputPak);
    }
    else
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Export Failed."));
    }
}
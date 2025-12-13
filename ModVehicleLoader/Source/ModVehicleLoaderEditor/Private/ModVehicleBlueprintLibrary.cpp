#include "ModVehicleBlueprintLibrary.h"
#include "Misc/MessageDialog.h"

#include "Engine/StaticMesh.h"
#include "Materials/MaterialInstanceConstant.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Engine/Blueprint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
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

#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformProcess.h"
#include "FileHelpers.h"

// =====================================================================
// Helper Functions

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

    for (const FAssetData& Data : AssetData)
    {
        if (Data.PackageName.ToString().StartsWith(TEXT("/Game/CarImports"))) continue;

        if (Data.AssetName.ToString().Contains(SlotName, ESearchCase::IgnoreCase))
        {
            return Cast<UMaterialInterface>(Data.GetAsset());
        }
    }
    return nullptr;
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
            UE_LOG(LogTemp, Log, TEXT("Matching Material: %s -> %s"), *ImportedMatName, *FoundMat->GetName());
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
        // 1. Create a Default Scene Root
        USCS_Node* RootNode = NewBP->SimpleConstructionScript->CreateNode(USceneComponent::StaticClass(), TEXT("SharedRoot"));
        NewBP->SimpleConstructionScript->AddNode(RootNode);

        // 2. Add Meshes
        for (UStaticMesh* Mesh : Meshes)
        {
            FString CompName = FString::Printf(TEXT("Comp_%s"), *Mesh->GetName());
            
            USCS_Node* MeshNode = NewBP->SimpleConstructionScript->CreateNode(UStaticMeshComponent::StaticClass(), FName(*CompName));
            UStaticMeshComponent* ComponentTemplate = Cast<UStaticMeshComponent>(MeshNode->ComponentTemplate);
            
            ComponentTemplate->SetStaticMesh(Mesh);
            ComponentTemplate->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
            ComponentTemplate->SetWorldScale3D(FVector(1.1f)); 

            NewBP->SimpleConstructionScript->AddNode(MeshNode);
            MeshNode->SetParent(RootNode);
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
    
    // Create Import Options
    FbxFactory->ImportUI = NewObject<UFbxImportUI>(FbxFactory);
    FbxFactory->ImportUI->MeshTypeToImport = FBXIT_StaticMesh;
    FbxFactory->ImportUI->bImportMaterials = true;
    FbxFactory->ImportUI->bImportTextures = true;
    FbxFactory->ImportUI->bImportMesh = true;
    FbxFactory->ImportUI->bAutomatedImportShouldDetectType = false;

    // Force vertices to absolute world coordinates
    // This ensures pivots stay at 0,0,0 relative to the mesh
    FbxFactory->ImportUI->StaticMeshImportData->bTransformVertexToAbsolute = true; 
    FbxFactory->ImportUI->StaticMeshImportData->bBakePivotInVertex = false;
    // -------------------------------------------

    FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
    TArray<UObject*> Assets = AssetToolsModule.Get().ImportAssetsAutomated(ImportData);

    if (Assets.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Import returned 0 assets. Scanning Temp folder manually..."));
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
    UE_LOG(LogTemp, Warning, TEXT("--- STARTING DIRECT PAK EXPORT ---"));

    const bool bPromptUser = false;
    const bool bSaveMapPackages = false;
    const bool bSaveContentPackages = true;
    const bool bFastSave = false;
    const bool bNotifyNoPackagesSaved = false;
    const bool bCanBeDeclined = false;
    FEditorFileUtils::SaveDirtyPackages(bPromptUser, bSaveMapPackages, bSaveContentPackages, bFastSave, bNotifyNoPackagesSaved, bCanBeDeclined);
    UE_LOG(LogTemp, Warning, TEXT("Force Saved Dirty Packages."));

    FString EngineDir = FPaths::ConvertRelativePathToFull(FPaths::EngineDir());
    FString UnrealPakExe = EngineDir + TEXT("Binaries/Win64/UnrealPak.exe");
    
    FString ProjectDir = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir());
    FString ContentDir = ProjectDir + TEXT("Content/CarImports/");
    
    FString OutputDir = FPaths::ProjectSavedDir() + TEXT("StagedMods/");
    FString OutputPak = OutputDir + TEXT("ModdedVehicle.pak");

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    PlatformFile.CreateDirectoryTree(*OutputDir);

    FString ResponseFilePath = OutputDir + TEXT("PakList.txt");
    FString ResponseContent;

    TArray<FString> FilesToPack;
    PlatformFile.FindFilesRecursively(FilesToPack, *ContentDir, nullptr);

    int32 FileCount = 0;
    for (const FString& File : FilesToPack)
    {
        FString RelativePath = File;
        FPaths::MakePathRelativeTo(RelativePath, *ProjectDir);
        FString MountPath = RelativePath.Replace(TEXT("Content/"), TEXT("../../../Game/"));
        
        ResponseContent += FString::Printf(TEXT("\"%s\" \"%s\"\n"), *File, *MountPath);
        FileCount++;
    }

    if (FileCount == 0)
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Export Failed: CarImports folder is empty on DISK! Did you save?"));
        return;
    }

    FFileHelper::SaveStringToFile(ResponseContent, *ResponseFilePath);

    FString Params = FString::Printf(TEXT("\"%s\" -create=\"%s\""), *OutputPak, *ResponseFilePath);

    UE_LOG(LogTemp, Warning, TEXT("Running UnrealPak: %s %s"), *UnrealPakExe, *Params);

    int32 ReturnCode = 0;
    FString Result;
    FPlatformProcess::ExecProcess(*UnrealPakExe, *Params, &ReturnCode, &Result, nullptr);

    if (ReturnCode == 0)
    {
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Export Successful! Check Saved/StagedMods"));
        UE_LOG(LogTemp, Warning, TEXT("Pak Success. Files packed: %d"), FileCount);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Pak Failed: %s"), *Result);
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Export Failed. Check Output Log."));
    }
}
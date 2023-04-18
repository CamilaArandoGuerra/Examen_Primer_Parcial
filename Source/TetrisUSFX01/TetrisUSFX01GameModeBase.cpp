// Copyright Epic Games, Inc. All Rights Reserved.


#include "TetrisUSFX01GameModeBase.h"
#include "Board.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

ATetrisUSFX01GameModeBase::ATetrisUSFX01GameModeBase() {
     // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    DefaultPawnClass = ABoard::StaticClass();
    siguientePosicionZ = 0;
}

void ATetrisUSFX01GameModeBase::BeginPlay()
{
  Super::BeginPlay();

  const float MinSpeed = 1.0f;
  const float MaxSpeed = 10.0f;

  // Generar una velocidad aleatoria inicial
  float FallSpeed = FMath::RandRange(MinSpeed, MaxSpeed);

  // Establecer la velocidad inicial de las piezas
  SetFallSpeed*(FallSpeed);
  // Configurar el temporizador para cambiar la velocidad cada 5 segundos
  const float ChangeInterval = 5.0f;
  GetWorldTimerManager().SetTimer(ChangeTimerHandle, this, &ATetrisUSFX01GameModeBase::ChangeFallSpeed, ChangeInterval, true);
}

void ATetrisUSFX01GameModeBase::ChangeFallSpeed()
{
    // Definir el rango de velocidades posibles
    const float MinSpeed = 1.0f;
    const float MaxSpeed = 10.0f;

    // Generar una nueva velocidad aleatoria
    float FallSpeed = FMath::RandRange(MinSpeed, MaxSpeed);

    // Establecer la nueva velocidad de las piezas
    SetFallSpeed*(FallSpeed);
}

void ATetrisUSFX01GameModeBase::SetFallSpeed(float NewSpeed)
{
    // Establecer la velocidad de las piezas
    // ...
}

//camara actor 
void ATetrisUSFX01GameModeBase::BeginPlay()
{
    // Call the parent class version of this function
    Super::BeginPlay();
    // Displays a red message on the screen for 10 seconds
    //GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Spawning un Block"));
    // Spawn an instance of the AMyFirstActor class at the
    //default location.
    /*FTransform SpawnLocation;
    SpawnedActor = GetWorld()->SpawnActor<ABlock>(ABlock::StaticClass(), SpawnLocation);
    SpawnedActor->SetActorRelativeLocation(FVector(0.0, 0.0, 0.0));

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Spawning un Piece"));
    SpawnedPiece = GetWorld()->SpawnActor<APiece>(APiece::StaticClass(), SpawnLocation);
    SpawnedPiece->SetActorRelativeLocation(FVector(0.0, 100.0, 0.0));
    SpawnedPiece->SpawnBlocks();*/

    for (TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        UE_LOG(LogTemp, Warning, TEXT("Find camera: %s"), *(it->GetFName().ToString()));
        if (it->GetFName() == TEXT("BoardCamera"))
        {
            APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
            PC->SetViewTargetWithBlend(*it, 0.5);
            break;
        }
    }

}

//spaunear pieza 
// Called every frame
void ATetrisUSFX01GameModeBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

   /* FTransform SpawnLocation;

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Spawning un Piece"));
    SpawnedPiece = GetWorld()->SpawnActor<APiece>(APiece::StaticClass(), SpawnLocation);
    SpawnedPiece->SetActorRelativeLocation(FVector(0.0, 100.0, 0.0));
    SpawnedPiece->SpawnBlocks();*/ 

}


void ATetrisUSFX01GameModeBase::DestroyActorFunction()
{
	if (SpawnedActor != nullptr)
   {
      // Displays a red message on the screen for 10 seconds
      GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("Actor Block destruido"));
      SpawnedActor->Destroy();
   }
}

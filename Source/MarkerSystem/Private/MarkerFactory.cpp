// Fill out your copyright notice in the Description page of Project Settings.


#include "MarkerFactory.h"

MarkerFactory::MarkerFactory()
{
}

MarkerFactory::~MarkerFactory()
{
}

void MarkerFactory::SpawnMarker(const TSubclassOf<AMarker>& markerClass, const EMarkerType type, const AMarkerSystemCharacter& character)
{
    if (!markerClass)
    {
        return;
    }

    auto cameraManager = character.GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
    if (!cameraManager)
    {
        return;
    }

    FVector startPosition = cameraManager->GetCameraLocation();
    FVector forwardVector = cameraManager->GetCameraRotation().Vector();

    const float raycastDistance = 3000.0f;
    FVector end = ((forwardVector * raycastDistance) + startPosition);

    FHitResult hitResult;
    FCollisionQueryParams collisionParams;
    collisionParams.AddIgnoredActor(&character);

    collisionParams.bTraceComplex = true;
    collisionParams.bReturnPhysicalMaterial = true;

    if (character.GetWorld()->LineTraceSingleByChannel(hitResult, startPosition, end, ECollisionChannel::ECC_Visibility, collisionParams))
    {
        AMarker* marker = character.GetWorld()->SpawnActor<AMarker>(markerClass, hitResult.Location, FRotator::ZeroRotator);
        if (marker)
        {
            marker->SetImageByType(type);
            marker->SetPosition(hitResult.Location);

            FTimerHandle fadeTimerHandle;
            character.GetWorld()->GetTimerManager().SetTimer(
                fadeTimerHandle,
                [this, marker]()
                {
                    marker->SetOpacity(0.25f);
                },
                1.5f,
                false
            );

            FTimerHandle removeTimerHandle;
            character.GetWorld()->GetTimerManager().SetTimer(
                removeTimerHandle,
                [this, marker]()
                {
                    RemoveMarker(marker);
                },
                3.0f,
                false
            );
        }
    }
}

void MarkerFactory::RemoveMarker(AMarker* marker)
{
    if (marker)
    {
        marker->Destroy();
    }
}

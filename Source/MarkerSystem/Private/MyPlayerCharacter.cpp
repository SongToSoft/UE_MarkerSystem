// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include <EnhancedInputComponent.h>
#include <MarkerFactory.h>
#include <Kismet/GameplayStatics.h>
#include <MarkerSystem/MarkerSystemGameMode.h>

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

    if (m_crossHairWidgetClass)
    {
        UUserWidget* crossHairWidget = CreateWidget<UUserWidget>(GetWorld(), m_crossHairWidgetClass);
        if (crossHairWidget)
        {
            crossHairWidget->AddToViewport();
        }
    }
	

    if (m_markerSelectorWidgetClass)
    {
        UUserWidget* markerSelectorWidget = CreateWidget<UUserWidget>(GetWorld(), m_markerSelectorWidgetClass);
        if (markerSelectorWidget)
        {
            markerSelectorWidget->AddToViewport();
        }
    }
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(m_spawnMarkerAction, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::PlaceMarker);

        //lambda?
        EnhancedInputComponent->BindAction(m_selectMarker_default, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::SelectMarkerDefault);
        EnhancedInputComponent->BindAction(m_selectMarker_green, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::SelectMarkerGreen);
        EnhancedInputComponent->BindAction(m_selectMarker_red, ETriggerEvent::Triggered, this, &AMyPlayerCharacter::SelectMarkerRed);
    }
}

void AMyPlayerCharacter::PlaceMarker()
{
    if (m_markerClass)
    {
        if (AMarkerSystemGameMode* gameMode = dynamic_cast<AMarkerSystemGameMode*>(UGameplayStatics::GetGameMode(this)))
        {
            gameMode->GetMarkerFactory()->SpawnMarker(m_markerClass, m_activeMarkerType, *this);
        }
    }
}

void AMyPlayerCharacter::SelectMarker(EMarkerType markerType)
{
    m_activeMarkerType = markerType;
}

void AMyPlayerCharacter::SelectMarkerDefault()
{
    SelectMarker(EMarkerType::DEFAULT);
}

void AMyPlayerCharacter::SelectMarkerGreen()
{
    SelectMarker(EMarkerType::GREEN);
}

void AMyPlayerCharacter::SelectMarkerRed()
{
    SelectMarker(EMarkerType::RED);
}
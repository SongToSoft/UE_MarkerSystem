// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\MarkerSystemCharacter.h"
#include <Marker.h>
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

UCLASS()
class MARKERSYSTEM_API AMyPlayerCharacter : public AMarkerSystemCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Marker")
	EMarkerType GetActiveMarkerType() const { return m_activeMarkerType; }

private:
	void PlaceMarker();

	void SelectMarkerDefault();
	void SelectMarkerGreen();
	void SelectMarkerRed();
	void SelectMarker(EMarkerType markerType);

private:

	UPROPERTY(EditAnywhere, Category = "Marker")
	TSubclassOf<AMarker> m_markerClass;
	UPROPERTY(EditAnywhere, Category = "Marker")
	TSubclassOf<UUserWidget> m_markerSelectorWidgetClass;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> m_crossHairWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Marker")
	EMarkerType m_activeMarkerType = EMarkerType::GREEN;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_spawnMarkerAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_selectMarker_default;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_selectMarker_green;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* m_selectMarker_red;
};

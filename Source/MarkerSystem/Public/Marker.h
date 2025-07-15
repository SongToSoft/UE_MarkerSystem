// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Marker.generated.h"

UENUM(BlueprintType)
enum class EMarkerType : uint8 {
	GREEN     UMETA(DisplayName = "Green"),
	RED       UMETA(DisplayName = "Red"),
	DEFAULT    UMETA(DisplayName = "Default"),
};

UCLASS()
class MARKERSYSTEM_API AMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPosition(const FVector& position);
	void SetOpacity(float opacity);
	void SetImageByType(EMarkerType type);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Marker")
	class UWidgetComponent* m_markerWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Marker")
	TSubclassOf<UUserWidget> m_markerWidgetClass;
};

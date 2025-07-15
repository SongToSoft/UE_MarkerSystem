// Fill out your copyright notice in the Description page of Project Settings.


#include "Marker.h"
#include <Kismet/GameplayStatics.h>
#include <Components/Image.h>

// Sets default values
AMarker::AMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	m_markerWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("MarkerWidget"));
	m_markerWidgetComponent->SetupAttachment(RootComponent);
	m_markerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	m_markerWidgetComponent->SetDrawSize(FVector2D(100, 100));

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/FirstPerson/UI/BP_MarkerWidget"));
	if (WidgetClassFinder.Succeeded())
	{
		m_markerWidgetClass = WidgetClassFinder.Class;
	}
}

// Called when the game starts or when spawned
void AMarker::BeginPlay()
{
	Super::BeginPlay();

	if (m_markerWidgetClass)
	{
		m_markerWidgetComponent->SetWidgetClass(m_markerWidgetClass);
		m_markerWidgetComponent->InitWidget();
	}
}

// Called every frame
void AMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMarker::SetPosition(const FVector& position)
{
    SetActorLocation(position);
}

void AMarker::SetOpacity(float opacity)
{
	UUserWidget* widget = Cast<UUserWidget>(m_markerWidgetComponent->GetWidget());
	if (widget)
	{
		UImage* image = Cast<UImage>(widget->GetWidgetFromName("Image"));

		if (image)
		{
			image->SetOpacity(opacity);
		}
	}
}


void AMarker::SetImageByType(EMarkerType type)
{
	UUserWidget* widget = Cast<UUserWidget>(m_markerWidgetComponent->GetWidget());
	if (widget)
	{
		UImage* image = Cast<UImage>(widget->GetWidgetFromName("Image"));

		UTexture2D* texture = nullptr;

		switch (type)
		{
		case EMarkerType::DEFAULT:
			texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/FirstPerson/Sprites/marker.marker'"));
			break;
		case EMarkerType::GREEN:
			texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/FirstPerson/Sprites/marker_green.marker_green'"));
			break;
		case EMarkerType::RED:
			texture = LoadObject<UTexture2D>(nullptr, TEXT("Texture2D'/Game/FirstPerson/Sprites/marker_red.marker_red'"));
			break;
		default:
			break;
		}

		if (texture)
		{
			image->SetBrushFromTexture(texture);
		}
	}
}
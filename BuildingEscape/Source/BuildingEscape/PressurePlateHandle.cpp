// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PressurePlateHandle.h"


// Sets default values for this component's properties
UPressurePlateHandle::UPressurePlateHandle()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPressurePlateHandle::BeginPlay()
{
	Super::BeginPlay();
   Owner = GetOwner();
   if (!PressurePlate)
   {
      UE_LOG(LogTemp, Error, TEXT("%s missing Pressure Plate!"), *Owner->GetName());
   }
}


// Called every frame
void UPressurePlateHandle::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassofActorsOnPlate() > TriggerMass)
   {
      DecreaseHeight.Broadcast();
   }
   else
   {
      IncreaseHeight.Broadcast();
   }
}

float UPressurePlateHandle::GetTotalMassofActorsOnPlate()
{
   float TotalMass = 0.f;
   
   // Find all the overlapping actors
   TArray<AActor*> OverlappingActors;
   if (!PressurePlate) { return TotalMass; }
   PressurePlate->GetOverlappingActors(OUT OverlappingActors);
   
   // Iterate through them addding their masses
   for (const auto& Actor : OverlappingActors)
   {
      TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
      UE_LOG(LogTemp, Warning, TEXT("%s on %s"), *Actor->GetName(), *Owner->GetName());
   }
   return TotalMass;
}


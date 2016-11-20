// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
   
   Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
   Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
   Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the Trigger Volume
   if (GetTotalMassofActorsOnPlate() > 30.f) // TOD make into a parmeter
   {
      OpenDoor();
      LastDoorOpenTime = GetWorld()->GetTimeSeconds();
   }
   
   // Check if it's time to close the door
   if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
   {
      CloseDoor();
   }
}

float UOpenDoor::GetTotalMassofActorsOnPlate()
{
   float TotalMass = 0.f;
   
   // Find all the overlapping actors
   TArray<AActor*> OverlappingActors;
   PressurePlate->GetOverlappingActors(OUT OverlappingActors);
   
   // Iterate through them addding their masses
   for (const auto& Actor : OverlappingActors)
   {
      TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
      UE_LOG(LogTemp, Warning, TEXT("%s on the pressure plate"), *Actor->GetName());
   }
   return TotalMass;
}

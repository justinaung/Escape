// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
private:
   // functions
   void OpenDoor();
   void CloseDoor();
   float GetTotalMassofActorsOnPlate(); // returns total mass in kg
   
   // members
   UPROPERTY(EditAnywhere)
   float OpenAngle = 80.f;
   
   UPROPERTY(EditAnywhere)
   ATriggerVolume* PressurePlate;
   
   UPROPERTY(EditAnywhere)
   float DoorCloseDelay = 1.f;
   
   float LastDoorOpenTime = 0.f;
   
   AActor* Owner; // The owning door
};

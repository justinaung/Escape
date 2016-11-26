// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PressurePlateHandle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPressurePlateEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPressurePlateHandle : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPressurePlateHandle();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

   // Returns total mass in kg
   float GetTotalMassofActorsOnPlate();
   
   UPROPERTY(BlueprintAssignable)
   FPressurePlateEvent DecreaseHeight;
   
   UPROPERTY(BlueprintAssignable)
   FPressurePlateEvent IncreaseHeight;

   
private:
   UPROPERTY(EditAnywhere)
   ATriggerVolume* PressurePlate = nullptr;
   
   UPROPERTY(EditAnywhere)
   float TriggerMass = 30.f;
   
   AActor* Owner = nullptr;
   
};

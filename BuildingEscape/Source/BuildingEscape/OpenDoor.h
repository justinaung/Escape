

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

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

   UPROPERTY(BlueprintAssignable)
   FDoorEvent OnOpen;
   
   UPROPERTY(BlueprintAssignable)
   FDoorEvent OnClose;
   
private:
   // functions
   float GetTotalMassofActorsOnPlate(); // returns total mass in kg
   
   // members
   UPROPERTY(EditAnywhere)
   float TriggerMass = 30.f;
   
   UPROPERTY(EditAnywhere)
   ATriggerVolume* PressurePlate = nullptr;
   
   AActor* Owner = nullptr; // The owning door
};

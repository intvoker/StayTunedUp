#pragma once

#include "STU_ControllerViewPointInterface.generated.h"

UINTERFACE(Blueprintable)
class STAYTUNEDUP_API USTU_ControllerViewPointInterface : public UInterface
{
	GENERATED_BODY()
};

class STAYTUNEDUP_API ISTU_ControllerViewPointInterface
{
	GENERATED_BODY()

public:
	virtual void GetControllerViewPoint(FVector& OutLocation, FRotator& OutRotation) const;
};

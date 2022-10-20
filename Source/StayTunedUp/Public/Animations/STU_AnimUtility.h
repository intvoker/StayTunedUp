// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STAYTUNEDUP_API STUAnimUtility
{
public:
	STUAnimUtility();
	~STUAnimUtility();

	static float GetMovementOffsetYaw(APawn* Pawn);
	
	static void SetRagdoll(AActor* Actor, USkeletalMeshComponent* Mesh);
};

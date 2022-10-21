// Stay Tuned Up Game

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class STAYTUNEDUP_API STU_AnimUtility
{
public:
	STU_AnimUtility();
	~STU_AnimUtility();

	static float GetMovementOffsetYaw(APawn* Pawn);

	static void SetRagdoll(AActor* Actor, USkeletalMeshComponent* Mesh);
};

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

	static void SetRagdoll(AActor* Actor, USkeletalMeshComponent* Mesh);
};

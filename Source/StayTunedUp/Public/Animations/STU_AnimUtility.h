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

	static float GetMovementOffsetYaw(const APawn* Pawn);

	static void SetRagdoll(AActor* Actor, USkeletalMeshComponent* Mesh);

	template <typename T>
	static T* FindNotifyByClass(UAnimSequenceBase* AnimSequenceBase);
};

template <typename T>
T* STU_AnimUtility::FindNotifyByClass(UAnimSequenceBase* AnimSequenceBase)
{
	if (!AnimSequenceBase)
		return nullptr;

	for (auto AnimNotifyEvent : AnimSequenceBase->Notifies)
	{
		if (auto AnimNotify = Cast<T>(AnimNotifyEvent.Notify))
		{
			return AnimNotify;
		}
	}

	return nullptr;
}

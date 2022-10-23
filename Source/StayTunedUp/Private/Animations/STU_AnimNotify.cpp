// Stay Tuned Up Game


#include "Animations/STU_AnimNotify.h"

void USTU_AnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnNotify.Broadcast(MeshComp);
}

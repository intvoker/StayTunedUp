// Stay Tuned Up Game


#include "Animations/STU_EquipFinishedAnimNotify.h"

void USTU_EquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	OnEquipFinishedNotify.Broadcast(MeshComp);
}

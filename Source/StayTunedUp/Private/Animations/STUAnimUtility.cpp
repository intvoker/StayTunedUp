// Stay Tuned Up Game


#include "Animations/STUAnimUtility.h"

STUAnimUtility::STUAnimUtility()
{
}

STUAnimUtility::~STUAnimUtility()
{
}

void STUAnimUtility::SetRagdoll(AActor* Actor, USkeletalMeshComponent* Mesh)
{
	Mesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));
	Actor->SetActorEnableCollision(true);

	Mesh->SetAllBodiesSimulatePhysics(true);
	Mesh->SetSimulatePhysics(true);
	Mesh->WakeAllRigidBodies();
	Mesh->bBlendPhysics = true;
}

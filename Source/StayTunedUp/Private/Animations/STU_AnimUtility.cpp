// Stay Tuned Up Game


#include "Animations/STU_AnimUtility.h"

float STU_AnimUtility::GetMovementOffsetYaw(const APawn* Pawn)
{
	const auto ForwardNormal = Pawn->GetActorForwardVector();
	const auto VelocityNormal = Pawn->GetVelocity().GetSafeNormal();

	const auto DotProduct = ForwardNormal | VelocityNormal;
	const auto CrossProduct = ForwardNormal ^ VelocityNormal;

	const auto Angle = FMath::RadiansToDegrees(FMath::Acos(DotProduct));
	const auto Sign = FMath::Sign(CrossProduct.Z);

	return CrossProduct.IsZero() ? Angle : Angle * Sign;
}

void STU_AnimUtility::SetRagdoll(AActor* Actor, USkeletalMeshComponent* Mesh)
{
	Mesh->SetCollisionProfileName(FName(TEXT("Ragdoll")));
	Actor->SetActorEnableCollision(true);

	Mesh->SetAllBodiesSimulatePhysics(true);
	Mesh->SetSimulatePhysics(true);
	Mesh->WakeAllRigidBodies();
	Mesh->bBlendPhysics = true;
}

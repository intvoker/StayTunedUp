// Stay Tuned Up Game


#include "AI/EQS/STU_PickupEnvQueryTest.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STU_Pickup.h"

USTU_PickupEnvQueryTest::USTU_PickupEnvQueryTest(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void USTU_PickupEnvQueryTest::RunTest(FEnvQueryInstance& QueryInstance) const
{
	const UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	const bool bWantsPickup = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		It.SetScore(TestPurpose, FilterType, CanPickup(ItemActor), bWantsPickup);
	}
}

bool USTU_PickupEnvQueryTest::CanPickup(AActor* ItemActor) const
{
	const auto STU_Pickup = Cast<ASTU_Pickup>(ItemActor);
	if (!STU_Pickup)
		return false;

	return STU_Pickup->IsActive();
}

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
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);

	bool bWantsPickup = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		const auto STU_Pickup = Cast<ASTU_Pickup>(ItemActor);
		if (!STU_Pickup)
		{
			continue;
		}

		It.SetScore(TestPurpose, FilterType, STU_Pickup->IsActive(), bWantsPickup);
	}
}

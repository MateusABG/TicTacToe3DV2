// Copyright Epic Games, Inc. All Rights Reserved.

#include "TicTacToeProjectile.h"
#include "TicTacToeGameState.h"
#include "TIcTacToePosition.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ATicTacToeProjectile::ATicTacToeProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &ATicTacToeProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ATicTacToeProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{  
	ATicTacToeGameState* gamestate = Cast<ATicTacToeGameState>(UGameplayStatics::GetGameState(this));
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		 
		Destroy();
		FString string;
		if (OtherActor->GetClass()->IsChildOf(ATIcTacToePosition::StaticClass())) {
			ATIcTacToePosition* actor = Cast<ATIcTacToePosition>(OtherActor);
			string = actor->Position;
			//if (GetLocalRole() == ROLE_Authority) {
				gamestate->Server_InputBlockPosition(string, 1);
				gamestate->Server_ChangeMaterial(actor, 1);
				//gamestate->whoShot = GetID();
			//} 
		}  
	}
}
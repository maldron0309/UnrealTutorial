// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
ABlasterCharacter::ABlasterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// PlayerController 가져오기
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		// SubSystem 가져오기
		UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		if (Subsystem)
		{
			// Input Mapping Context 추가
			Subsystem->AddMappingContext(BlasterInputContext, 0);
		}
	}
}

// Called every frame
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent -> BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent -> BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	}
}

void ABlasterCharacter::Move(const FInputActionValue& Value)
{
	// TODO
	// 1. 컨트롤러의 nullptr 여부 검사
	// 2. Input 가져오기 (FVector2D Type)
	// 3. 컨트롤러의 회전값 가져오기
	// 4. 캐릭터의 YawRotation 가져오기 (캐릭터의 회전은 수평으로만 이루어짐)
	// 5. 회전행렬 이용하여 캐릭터가 바라보는 방향의 Forward 벡터 가져오기
	// 6. 회전행렬 이용하여 캐릭터의 오른쪽 방향 벡터 가져오기
	// 7. 전진벡터 Y값, 회전벡터 X값을 CharacterMovement에 적용

	if (!Controller) // 1
	{
		return;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>(); // 2

	const FRotator Rotation = Controller->GetControlRotation(); // 3
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f); // 4
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 5
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // 6
	AddMovementInput(ForwardDirection, MovementVector.Y); // 7
	AddMovementInput(RightDirection, MovementVector.X);

}


void ABlasterCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

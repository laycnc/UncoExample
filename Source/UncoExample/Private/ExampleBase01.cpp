// Fill out your copyright notice in the Description page of Project Settings.

#include "ExampleBase01.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UncoAsyncSystemLibrary.h"

// Sets default values
AExampleBase01::AExampleBase01()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent =
	    CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent0"));
	StaticMeshComponent->SetCollisionProfileName(
	    UCollisionProfile::BlockAll_ProfileName);
	StaticMeshComponent->Mobility = EComponentMobility::Movable;
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->bUseDefaultCollision = true;

	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AExampleBase01::BeginPlay()
{
	Super::BeginPlay();

	// 非同期での初期化を行う
	AsyncBeginPlay();
}

// Called every frame
void AExampleBase01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 非同期初期化
unco::FObjectTask AExampleBase01::AsyncBeginPlay()
{
	UKismetSystemLibrary::PrintString(
	    this, FString::Printf(TEXT("AsyncDelay:%f"), DelayBeginTime));

	// 一定時間待機する
	co_await unco::AsyncDelay(this, DelayBeginTime);

	UKismetSystemLibrary::PrintString(this,
	                                  FString::Printf(TEXT("AsyncDelay Finish")));

	UKismetSystemLibrary::PrintString(
	    this, FString::Printf(TEXT("AsyncLoadAsset:%s"), *LoadMeshPath.ToString()));

	// メッシュの非同期ロードを行う
	UStaticMesh* Mesh = co_await unco::AsyncLoadAsset(this, LoadMeshPath);

	if ( !IsValid(Mesh) )
	{
		UKismetSystemLibrary::PrintString(this, TEXT("Load Failed"));
		co_return;
	}

	// ログを出す
	UKismetSystemLibrary::PrintString(this, TEXT("Load Success"));

	// 読み込んだメッシュを設定する
	StaticMeshComponent->SetStaticMesh(Mesh);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExampleBase01.generated.h"
#include "GameFramework/Actor.h"
#include "UncoObjectTask.h"
class UStaticMeshComponent;

UCLASS()
class UNCOEXAMPLE_API AExampleBase01 : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExampleBase01();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 非同期初期化
	unco::FObjectTask AsyncBeginPlay();

private:
	// 初期化待機時間
	UPROPERTY(EditAnywhere, Category = "Config")
	float DelayBeginTime = 5.f;

	// ロードするメッシュ
	UPROPERTY(EditAnywhere, Category = "Config")
	TSoftObjectPtr<UStaticMesh> LoadMeshPath;

	UPROPERTY(Category = StaticMeshActor,
	          VisibleAnywhere,
	          BlueprintReadOnly,
	          meta = (ExposeFunctionCategories =
	                      "Mesh,Rendering,Physics,Components|StaticMesh",
	                  AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
};

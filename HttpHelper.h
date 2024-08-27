// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "HttpHelper.generated.h"

UENUM(BlueprintType)
enum class EActionType : uint8
{
	SPAWN UMETA(DisplayName = "SPAWN"),
	FEEDING UMETA(DisplayName = "FEEDING"),
	HELLO UMETA(DisplayName = "HELLO"),
	HIDE UMETA(DisplayName = "HIDE"),
	BELLY UMETA(DisplayName = "BELLY"),
	GETCLOSE UMETA(DisplayName = "GETCLOSE"),
	ENDCLOSE UMETA(DisplayName = "ENDCLOSE"),
	SPIN UMETA(DisplayName = "SPIN"),
	RESET UMETA(DisplayName = "RESET")
};

USTRUCT(Atomic, BlueprintType)
struct FST_Status
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool spawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool feeding;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hello;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool hide;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool belly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool getclose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool endclose;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool spin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool reset;
};

UCLASS()
class AQUA_MOBILE_API AHttpHelper : public AActor
{
	GENERATED_BODY()
	
public:	
	AHttpHelper(const class FObjectInitializer& ObjectInitializer);
	void BeginPlay();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "HTTP")
		FString webUrl;


public:
	UPROPERTY(BlueprintReadWrite,VisibleAnywhere, Category = "HTTP")
		FST_Status Status;

	UFUNCTION(BlueprintCallable, Category = "HTTP")
		void SetIP(FString ip);

public:
	FHttpModule* Http;

	UFUNCTION(BlueprintCallable, Category = "HTTP")
		void GetStatusQuery();
	void OnResponseGetStatusQueryReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);


	UFUNCTION(BlueprintCallable, Category = "HTTP")
		void PostStatusQuery(FString deviceID, EActionType actionType);
	void OnResponsePostStatusQueryReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

};



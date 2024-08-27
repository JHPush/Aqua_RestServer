// Fill out your copyright notice in the Description page of Project Settings.


#include "HttpHelper.h"
#include "Kismet/KismetStringLibrary.h"

// Sets default values
AHttpHelper::AHttpHelper(const class FObjectInitializer& ObjectInitializer)
{
	Http = &FHttpModule::Get();
}
// Called when the game starts or when spawned

void AHttpHelper::BeginPlay()
{
	Super::BeginPlay();
}

void AHttpHelper::SetIP(FString ip) {
	webUrl = ip;
}


void AHttpHelper::GetStatusQuery()
{

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	Request->OnProcessRequestComplete().BindUObject(this, &AHttpHelper::OnResponseGetStatusQueryReceived);

	Request->SetURL("http://" + webUrl + "/status");
	Request->SetVerb("GET");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->ProcessRequest();
}



void AHttpHelper::OnResponseGetStatusQueryReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//if (!bWasSuccessful) return;
	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		Status.id = JsonObject->GetStringField("id");
		Status.spawn = JsonObject->GetBoolField("spawn");
		Status.feeding = JsonObject->GetBoolField("feeding");
		Status.hello = JsonObject->GetBoolField("hello");
		Status.hide = JsonObject->GetBoolField("hide");
		Status.belly = JsonObject->GetBoolField("belly");
		Status.getclose = JsonObject->GetBoolField("getclose");
		Status.endclose = JsonObject->GetBoolField("endclose");
		Status.spin = JsonObject->GetBoolField("spin");
		Status.reset = JsonObject->GetBoolField("reset");
	}
}


void AHttpHelper::PostStatusQuery(FString deviceID, EActionType actionType)
{

	TSharedRef<IHttpRequest> Request = Http->CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();

	RequestObj->SetStringField("id", deviceID);
	RequestObj->SetBoolField("spawn", false);
	RequestObj->SetBoolField("feeding", false);
	RequestObj->SetBoolField("hello", false);
	RequestObj->SetBoolField("hide", false);
	RequestObj->SetBoolField("belly", false);
	RequestObj->SetBoolField("getclose", false);
	RequestObj->SetBoolField("endclose", false);
	RequestObj->SetBoolField("spin", false);
	RequestObj->SetBoolField("reset", false);

	switch (actionType) {
	case EActionType::SPAWN:
		RequestObj->SetBoolField("spawn", true);
		break;
	case EActionType::FEEDING:
		RequestObj->SetBoolField("feeding", true);
		break;
	case EActionType::HELLO:
		RequestObj->SetBoolField("hello", true);
		break;
	case EActionType::HIDE:
		RequestObj->SetBoolField("hide", true);
		break;
	case EActionType::BELLY:
		RequestObj->SetBoolField("belly", true);
		break;
	case EActionType::GETCLOSE:
		RequestObj->SetBoolField("getclose", true);
		break;
	case EActionType::ENDCLOSE:
		RequestObj->SetBoolField("endclose", true);
		break;
	case EActionType::SPIN:
		RequestObj->SetBoolField("spin", true);
		break;
	case EActionType::RESET:
		RequestObj->SetBoolField("reset", true);
		break;
	}

	FString RequestBody;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);

	Request->OnProcessRequestComplete().BindUObject(this, &AHttpHelper::OnResponsePostStatusQueryReceived);
	Request->SetURL("http://" + webUrl + "/status");
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", TEXT("application/json"));
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}



void AHttpHelper::OnResponsePostStatusQueryReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	//if (!bWasSuccessful) return;

	//Create a pointer to hold the json serialized data
	TSharedPtr<FJsonObject> JsonObject;

	//Create a reader pointer to read the json data
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());

	//Deserialize the json data given Reader and the actual object to deserialize
	if (FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		//Get the value of the json object by field name
		Status.id = JsonObject->GetStringField("id");
		Status.spawn = JsonObject->GetBoolField("spawn");
		Status.feeding = JsonObject->GetBoolField("feeding");
		Status.hello = JsonObject->GetBoolField("hello");
		Status.hide = JsonObject->GetBoolField("hide");
		Status.belly = JsonObject->GetBoolField("belly");
		Status.getclose = JsonObject->GetBoolField("getclose");
		Status.endclose = JsonObject->GetBoolField("endclose");
		Status.spin = JsonObject->GetBoolField("spin");
		Status.reset = JsonObject->GetBoolField("reset");

		//Output it to the engine
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, Status.id);
		GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Green, UKismetStringLibrary::Conv_BoolToString(bWasSuccessful));
	}
}


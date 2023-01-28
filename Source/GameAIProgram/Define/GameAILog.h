#pragma once
#include "DebugIndexDefine.h"

template <typename FmtType, typename... Types>
void AILog(uint64 InDebugIndex, const FmtType& InFmt, Types... InArgs)
{
	const FString& Message = FString::Printf(InFmt, InArgs...);
	GEngine->AddOnScreenDebugMessage(InDebugIndex, FDebugIndex::OnDisplayTime, FColor::Green, Message);
	
}

#define AI_LOG(DebugIndex, Message, ...) AILog(DebugIndex, Message, __VA_ARGS__);

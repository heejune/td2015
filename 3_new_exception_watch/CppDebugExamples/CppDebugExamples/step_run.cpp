
#include "stdafx.h"
#include "step_run.h"

#include <memory>
#include <string>
#include <functional>
#include <array>


void specific_into()
{
	std::shared_ptr<EventHandler> pHandler(new EventHandler());
	std::shared_ptr<Packet> packet(new Packet());

	auto ret = pHandler->OnEvent(GetHandler(packet->GetType()), packet->GetPayload());

}

#pragma once

template<typename T>
void Safe_Delete(T& rObj)
{
	if (nullptr != rObj)
	{
		delete rObj;
		rObj = nullptr;
	}
}

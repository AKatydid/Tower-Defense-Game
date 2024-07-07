#ifndef _COIN_MANAGER_H_
#define _COIN_MANAGER_H_

#include "manager/manager.h"
#include "manager/config_manager.h"

#include <vector>

class CoinManager : public Manager<CoinManager>
{
	friend class Manager<CoinManager>;

public:
	

public:
	void increase_coin(double val)
	{
		num_coin += val;
	}

	void decrease_coin(double val)
	{
		num_coin -= val;

		if (num_coin < 0)
			num_coin = 0;
	}

protected:
	CoinManager() = default;
	~CoinManager() = default;

private:
	double num_coin = 0;
};


#endif // !_COIN_MANAGER_H_

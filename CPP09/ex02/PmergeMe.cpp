#include "PmergeMe.hpp"

/* ┌──────────────────┐ */
/* │   COSNTRUCTORS   │ */
/* └──────────────────┘ */
PmergeMe::PmergeMe(void)
{ }

PmergeMe::PmergeMe(const PmergeMe& other)
{(void)other;}

/* ┌───────────────────┐ */
/* │   DECOSNTRUCTOR   │ */
/* └───────────────────┘ */

PmergeMe::~PmergeMe(void)
{ }

/* ┌───────────────┐ */
/* │   OVERLOADS   │ */
/* └───────────────┘ */

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	(void)other;
	return (*this);
}

/* ┌──────────────────────┐ */
/* │   MEMBER FUNCTIONS   │ */
/* └──────────────────────┘ */

static int next_jacobshtel_index(bool reset, size_t size)
{
	static unsigned int j_prev = 0;
	static unsigned int j_curr = 0;
	static unsigned int countdown = 0;

	if (reset)
	{
		j_prev = 0;
		j_curr = 0;
		countdown = 0;
		return (-1);
	}

	while (true)
	{
		if (countdown > j_prev)
		{
			unsigned int result = countdown;
			countdown--;
			return ((int)(result - 1));
		}
		if (j_curr == 0)
		{
			j_prev = 0;
			j_curr = 1;
		}
		else
		{
			unsigned int next = j_curr + 2 * j_prev;
			j_prev = j_curr;
			j_curr = next;
		}
		if (j_prev >= size)
			return (-1);
		countdown = (j_curr > size) ? size : j_curr;
	}
}

static size_t binary_insert_vec(std::vector<int>& sorted, int value, size_t bound)
{
	if (bound > sorted.size())
		bound = sorted.size();
	size_t low = 0;
	size_t high = bound;
	while (low < high)
	{
		size_t mid = low + (high - low) / 2;
		if (sorted[mid] < value)
			low = mid + 1;
		else
			high = mid;
	}
	sorted.insert(sorted.begin() + low, value);
	return (low);
}

static size_t binary_insert_deq(std::deque<int>& sorted, int value, size_t bound)
{
	if (bound > sorted.size())
		bound = sorted.size();
	size_t low = 0;
	size_t high = bound;
	while (low < high)
	{
		size_t mid = low + (high - low) / 2;
		if (sorted[mid] < value)
			low = mid + 1;
		else
			high = mid;
	}
	sorted.insert(sorted.begin() + low, value);
	return (low);
}

void PmergeMe::vector_sorter(std::vector<int>& input)
{
	if (input.size() <= 1)
		return;

	std::vector<std::pair<long,long> > pairs;
	int extra =  (input.size() % 2 == 1) ? input.back() : -1;


	int lo;
	int hi;
	for (size_t i = 0; i + 1 < input.size(); i += 2)
	{
        lo = input[i];
		hi = input[i + 1];
        if (lo > hi) std::swap(lo, hi);
        pairs.push_back(std::make_pair(hi, lo));
    }

	std::vector<int> winners;
	for(size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
	vector_sorter(winners);

	std::vector<int> losers;
	std::vector<size_t> partnerPos;
	std::vector<bool> used(pairs.size(), false);
	for (size_t i = 0; i < winners.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == winners[i])
			{
				losers.push_back(pairs[j].second);
				partnerPos.push_back(i);
				used[j] = true;
				break;
			}
		}
	}

	input = winners;
	next_jacobshtel_index(true, 0);
	int idx;
	while ((idx = next_jacobshtel_index(false, losers.size())) != -1)
	{
		size_t bound = partnerPos[idx];
		size_t pos = binary_insert_vec(input, losers[idx], bound);

		for (size_t k = 0; k < partnerPos.size(); k++)
			if (partnerPos[k] >= pos)
				partnerPos[k]++;
	}
	if (extra != -1)
		binary_insert_vec(input, extra, input.size());

}

void PmergeMe::deque_sorter(std::deque<int>& input)
{
	if (input.size() <= 1)
		return;

	std::deque<std::pair<long,long> > pairs;
	int extra =  (input.size() % 2 == 1) ? input.back() : -1;


	int lo;
	int hi;
	for (size_t i = 0; i + 1 < input.size(); i += 2)
	{
        lo = input[i];
		hi = input[i + 1];
        if (lo > hi) std::swap(lo, hi);
        pairs.push_back(std::make_pair(hi, lo));
    }

	std::deque<int> winners;
	for(size_t i = 0; i < pairs.size(); i++)
		winners.push_back(pairs[i].first);
	deque_sorter(winners);

	std::deque<int> losers;
	std::deque<size_t> partnerPos;
	std::vector<bool> used(pairs.size(), false);
	for (size_t i = 0; i < winners.size(); i++)
	{
		for (size_t j = 0; j < pairs.size(); j++)
		{
			if (!used[j] && pairs[j].first == winners[i])
			{
				losers.push_back(pairs[j].second);
				partnerPos.push_back(i);
				used[j] = true;
				break;
			}
		}
	}

	input = winners;
	next_jacobshtel_index(true, 0);
	int idx;
	while ((idx = next_jacobshtel_index(false, losers.size())) != -1)
	{
		size_t bound = partnerPos[idx];
		size_t pos = binary_insert_deq(input, losers[idx], bound);

		for (size_t k = 0; k < partnerPos.size(); k++)
			if (partnerPos[k] >= pos)
				partnerPos[k]++;
	}
	if (extra != -1)
		binary_insert_deq(input, extra, input.size());

}
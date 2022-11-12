std::vector<int>find_num_chars(std::vector<std::string>& s)
{	//size must be at least 2 for function to run *
	//sort the string to get the vector in lexicographical order return front and back. *
	//to find the shortest string create a variable min with a size of first elements size. Traverse the vector checking the size of each string. first index string.size() will be assigned to shortest each subsequent string will be compared using < operator to determine if shortest.
	 //traverse vector again to find size == shortest and push those string to the back of a vector.
	// do the same thing to find largest string but with max and > operator.
	if (s.size() >= 2)
	{
		std::sort(s.begin(), s.end());
		std::cout << "Shortest string lexicographically is: " << s.front() << " and the greatest string lexicographically is: " << s.back() << "\n\n\n";
		std::cout << "Shortest string(s)...\n";
		int min = s.front().size();
		int max = s.front().size();
		for (const auto& target : s)						//find shortest string.size() and largest
		{
			if (target.size() < static_cast<unsigned>(min))
			{
				min = target.size();
			}
			else if (target.size() > static_cast<unsigned>(max))
			{
				max = target.size();
			}
		}
		std::vector<std::string> shortest_strings;
		std::vector<std::string> largest_strings;
		for (const auto& target : s)
		{
			if (target.size() == min)
			{
				shortest_strings.push_back(target);
			}
			else if (target.size() == max)
			{
				largest_strings.push_back(target);
			}
		}
		display(shortest_strings);
		std::cout << "Largest string(s)...\n";
		display(largest_strings);
		std::vector<int> sizes;
		for (const auto& target : s)
		{
			sizes.push_back(target.size());
		}
		return sizes;
	}
}

#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <list>
#include <vector>

template <typename T>
int cop4530::HashTable<T>::getSize() const   //hash size
{
   return currSize;
}
template <typename T>
size_t cop4530::HashTable<T>::tableSize() const   //vec size
{
   return table.size();
}
template <typename T>
bool cop4530::HashTable<T>::load(const char*filename)
{
   ifstream is;
   is.open(filename);
   if(! is){
      cout<<"Cannot open file "<<filename<<endl;
      return false;
   }
   else
   {
      T i;
      while(is.eof()!=true)   //until end of file
      {
	 is>>i;
	 is.ignore();
	 insert(i);
      }
      cout<<"Dictionary loaded successfully."<<endl;
      is.close();
      return true;
   }
}
template <typename T>
bool cop4530::HashTable<T>::write_to_file(const char*filename) const
{
   ofstream os;   
   os.open(filename);
   if(! os)
      return false;
   else
      {
         for(const auto & currIdx:table){   //iterate thru each list in each index
	    for(const auto & i:currIdx)
		os<<i<<endl;
	 }
      os.close();
      }
}
template <typename T>
void cop4530::HashTable<T>::dump() const
{
   int p=0;
   for(const auto & currIdx : table)
   {
      cout<<"v["<<p<<"]: ";
      for(const auto & i:currIdx){
         cout<<i<<"\t";
      }
      p++;
      cout<<endl;
   } 
}
template <typename T>
bool cop4530::HashTable<T>::remove(const T &x)
{
   if(contains(x)==false)   //if dne return false
      return false;
   auto & currIdx = table[myhash(x)];   //access list
   auto itr=find(begin(currIdx), end(currIdx), x);   //find spot in arr
   currIdx.erase(itr);
   currSize--;
   return true;
}
template <typename T>
bool cop4530::HashTable<T>::insert(const T &x)
{
   if(contains(x)==true)   //if alr exist send false
      return false;
   auto & currIdx = table[myhash(x)];
   currIdx.push_back(x);   //append list
   currSize++;
   if(currSize>table.size())   //rehash if neccessary
      rehash();
   return true;
}
template <typename T>
bool cop4530::HashTable<T>::insert(T &&x)
{
   if(contains(x)==true)   //if alr exist send false
      return false;
   auto & currIdx = table[myhash(x)];
   currIdx.push_back(x);   //append list
   currSize++;
   if(currSize>table.size())   //rehash if neccessary
      rehash();
   return true;
}
template <typename T>
cop4530::HashTable<T>::~HashTable()
{
   makeEmpty();
}
template <typename T>
bool cop4530::HashTable<T>::contains(const T &x) const
{
   auto & currIdx = table[myhash(x)];
   if(find(begin(currIdx), end(currIdx), x)!= end(currIdx))
      return true;
   else
      return false;
}
template <typename T>
void cop4530::HashTable<T>::clear()
{
   makeEmpty();
}
template <typename T>
void cop4530::HashTable<T>::makeEmpty()
{
   for(auto & thistable : table)   //go to each ind and delete list
      thistable.clear();
   currSize=0;
}
template <typename T>
void cop4530::HashTable<T>::rehash()
{
   vector<list<T>> oldTable=table;   //store old hash
   table.resize((prime_below(2*table.size())));   //double size
   for(auto& temptable:table)   //clear table
      temptable.clear();
   currSize=0;
   for(auto & temptable : oldTable)   //copy data
      for(auto & x: temptable)
	 insert(x);
}
template <typename T>
size_t cop4530::HashTable<T>::myhash(const T &x) const 
{
    std::hash<T> tHash;
    return tHash(x) % table.size();
}
template <typename T>
cop4530::HashTable<T>::HashTable(size_t size)
{
   currSize=0;
   table.resize(prime_below(size));
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename T>
unsigned long HashTable<T>::prime_below (long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename T>
void HashTable<T>::setPrimes(std::vector<long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}


#ifndef __JESS_MAP_HPP__
#define __JESS_MAP_HPP__

#include <map>
#include <assert.h>
#include <functional>
#include <stdio.h>

#include <Nebula/Util/WrapperTyped.hpp>

namespace Neb {
	template <class T> class Map {
		public:
			typedef std::shared_ptr<T>			shared_type;

			typedef Neb::WrapperTyped<T>			mapped_type;

			typedef std::weak_ptr< Neb::Factory<T> >	factory_weak;
			
			typedef std::map<int,mapped_type>		map_type;
			
			typedef typename map_type::iterator		iterator;
			typedef typename map_type::value_type		value_type_const;
			typedef std::pair<int,mapped_type>		value_type;
			
			/** @brief Constructor */
			Map(factory_weak factory): factory_(factory), next_(0) {}
			/*void		add(value_type& p) {
			  p.first = next_++;
			  map_.insert(p);
			  }*/
			/** */
			void				push_back(shared_type& u) {
				assert(u);
				
				u->i(next_);
				
				mapped_type m(factory_, u);

				map_.emplace(next_, m);

				next_++;
			}
			/** */
			iterator			find(int a) {
				auto it = map_.find( a );

				return it;
			}
			/** */
			void				clear() {
				map_.clear();
			}
			/** */
			iterator			begin() {
				return map_.begin();
			}
			/** */
			iterator			end() {
				return map_.end();
			}
			/** */
			iterator			erase(iterator it) {
				it = map_.erase(it);
				return it;
			}
			//private:
			factory_weak	factory_;
			int		next_;
			map_type	map_;

	};	
}

#endif






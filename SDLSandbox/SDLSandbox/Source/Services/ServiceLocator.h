/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include "IServiceProvider.h"

#include <iostream>
#include <typeindex>
#include <map>

namespace Challenge {

	class ServiceLocator {

		public:
			static ServiceLocator* getInstance ();

			/// <summary>
			/// Returns a service provider for a provided type of service.
			/// </summary>
			/// <returns>The service provider, or nullptr if no provider is found.</returns>
			template <typename TService>
			TService* getServiceProvider () {
				auto servicePair = this->services.find (typeid (TService));

				if (servicePair == this->services.end ()) {
					std::cerr << "Could not find service: " << typeid (TService).name () << std::endl;
					return nullptr;
				}

				return (TService*) servicePair->second;
			}

			/// <summary>
			/// Registers a service provider.
			/// </summary>
			void registerServiceProvider (IServiceProvider* service);

			/// <summary>
			/// Unregisters a service provider.
			/// </summary>
			void unregisterServiceProvider (IServiceProvider* service);

		private:
			static ServiceLocator* instance;

			std::map<std::type_index, IServiceProvider*> services;

			ServiceLocator ();
	};

	typedef ServiceLocator TheServiceLocator;
}


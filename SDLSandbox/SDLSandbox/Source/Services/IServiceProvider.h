/* 
* Miniclip Challenge: Poison Strike
* @author Nelson Rodrigues
*/

#pragma once

#include <typeindex>

namespace Challenge {

	class IServiceProvider {

		public:		
			IServiceProvider () {};
			virtual ~IServiceProvider () {};

			// no copy operations
			IServiceProvider (const IServiceProvider&) = delete;
			IServiceProvider& operator=(const IServiceProvider&) = delete;

			// no move operations
			IServiceProvider (IServiceProvider&&) = delete;
			IServiceProvider& operator = (IServiceProvider&&) = delete;

			/// <summary>
			/// Returns the type of interface which will be used to communicate with this kind of service.
			/// Caution: Service must either be this type, or inherit from this type.
			/// </summary>
			/// <returns>Type of interface.</returns>
			virtual std::type_index getInterfaceType () = 0;
		
			/// <summary>
			/// Provides a certain service, by registering at the ServiceLocator as a service provider.
			/// </summary>
			void provideService ();

			/// <summary>
			/// Cancels service, by unregistering from the ServiceLocator as a service provider.
			/// </summary>
			void revokeService ();
	};
}
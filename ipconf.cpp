#include <stdio.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

// Link with Iphlpapi.lib and ws2_32.lib
// #pragma comment(lib, "Iphlpapi.lib")
// #pragma comment(lib, "ws2_32.lib")

void showAdaptersInfo() {
  IP_ADAPTER_ADDRESSES* adapter_addresses(NULL);
  IP_ADAPTER_ADDRESSES* adapter(NULL);
  
  DWORD adapter_addresses_buffer_size = 16 * 1024;
  
  for (int attempts = 0; attempts != 3; ++attempts) {
    adapter_addresses = (IP_ADAPTER_ADDRESSES*) malloc(adapter_addresses_buffer_size);
    
    ULONG flags = GAA_FLAG_SKIP_ANYCAST | GAA_FLAG_SKIP_MULTICAST | GAA_FLAG_SKIP_DNS_SERVER | GAA_FLAG_SKIP_FRIENDLY_NAME;
    DWORD error = GetAdaptersAddresses(AF_UNSPEC, flags, NULL, adapter_addresses, &adapter_addresses_buffer_size);
    
    if (error == ERROR_SUCCESS) {
      break;
    }
    else if (error == ERROR_BUFFER_OVERFLOW) {
      free(adapter_addresses);
      adapter_addresses = NULL;
      continue;
    }
    else {
      free(adapter_addresses);
      adapter_addresses = NULL;
      printf("Unhandled error! Exit.\n");
      return;
    }
  }

  for (adapter = adapter_addresses; adapter != NULL; adapter = adapter->Next) {
    if (adapter->IfType == IF_TYPE_SOFTWARE_LOOPBACK) continue;
    
    // printf("[ADAPTER]: %S\n", adapter->Description);
    // printf("[NAME]:    %S\n", adapter->FriendlyName);

    // Parse all IPv4 addresses
    for (IP_ADAPTER_UNICAST_ADDRESS* address = adapter->FirstUnicastAddress; address != NULL; address = address->Next) {
      auto family = address->Address.lpSockaddr->sa_family;
      if (family == AF_INET) {
        SOCKADDR_IN* ipv4 = reinterpret_cast<SOCKADDR_IN*>(address->Address.lpSockaddr);
        char str_buffer[16] = {0};
        inet_ntop(AF_INET, &(ipv4->sin_addr), str_buffer, 16);
        printf("[%16s]: ", str_buffer);
      }
    }
    printf("%S\n", adapter->FriendlyName);
  }
  
  free(adapter_addresses);
  adapter_addresses = NULL;
}

int main() {
  printf("== ipconf ==\n");
  showAdaptersInfo();
  return 0;
}

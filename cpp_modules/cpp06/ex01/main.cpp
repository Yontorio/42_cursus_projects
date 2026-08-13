#include <iostream>
#include "Serializer.hpp"

int main() {
    std::cout << "|===============TEST 1: Stack Allocated Data===============|" << std::endl;
    {
        Data myData;
        myData.i_data = 42;
        myData.f_data = 13.37f;

        Data* originalPtr = &myData;
        std::cout << "Original Pointer Address: " << originalPtr << std::endl;
        std::cout << "Original Data contents: " << std::endl;
        std::cout << "  - i_data: " << originalPtr->i_data << std::endl;
        std::cout << "  - f_data: " << originalPtr->f_data << std::endl;

        // Serialization
        uintptr_t raw = Serializer::serialize(originalPtr);
        std::cout << "\nSerialized uintptr_t value (hex): 0x" << std::hex << raw << std::dec 
                    << " (dec): " << raw << std::endl;

        // Deserialization
        Data* deserializedPtr = Serializer::deserialize(raw);
        std::cout << "Deserialized Pointer Address: " << deserializedPtr << std::endl;

        // Checks
        if (deserializedPtr == originalPtr)
            std::cout << "\n[SUCCESS] Deserialized pointer matches the original pointer!" << std::endl;
        else
            std::cout << "\n[FAILURE] Pointers do not match!" << std::endl;

        std::cout << "Deserialized Data contents: " << std::endl;
        std::cout << "  - i_data: " << deserializedPtr->i_data << std::endl;
        std::cout << "  - f_data: " << deserializedPtr->f_data << std::endl;

        if (deserializedPtr->i_data == myData.i_data &&
            deserializedPtr->f_data == myData.f_data)
            std::cout << "[SUCCESS] Data members are intact and identical!" << std::endl;
        else
            std::cout << "[FAILURE] Data members were modified or corrupted!" << std::endl;
    }

    std::cout << "\n|===============TEST 2: Heap Allocated Data===============|" << std::endl;
    {
        Data* originalPtr = new Data;
        originalPtr->i_data = 42;
        originalPtr->f_data = 13.37f;

        std::cout << "Original Pointer Address: " << originalPtr << std::endl;
        std::cout << "Original Data contents: " << std::endl;
        std::cout << "  - i_data: " << originalPtr->i_data << std::endl;
        std::cout << "  - f_data: " << originalPtr->f_data << std::endl;

        // Serialization
        uintptr_t raw = Serializer::serialize(originalPtr);
        std::cout << "Serialized uintptr_t value (hex): 0x" << std::hex << raw 
                   << std::dec << " (dec): " << raw << std::endl;

        // Deserialization
        Data* deserializedPtr = Serializer::deserialize(raw);
        std::cout << "Deserialized Pointer Address: " << deserializedPtr << std::endl;

        // Checks
        if (deserializedPtr == originalPtr)
            std::cout << "\n[SUCCESS] Deserialized pointer matches the original pointer!" << std::endl;
        else
            std::cout << "\n[FAILURE] Pointers do not match!" << std::endl;

        std::cout << "Deserialized Data contents: " << std::endl;
        std::cout << "  - i_data: " << deserializedPtr->i_data << std::endl;
        std::cout << "  - f_data: " << deserializedPtr->f_data << std::endl;

        delete originalPtr;
    }

    std::cout << "\n|===============TEST 3: NULL Pointer Handling===============|" << std::endl;
    {
        Data* originalPtr = NULL;
        std::cout << "Original Pointer Address: " << originalPtr << std::endl;

        // Serialization
        uintptr_t raw = Serializer::serialize(originalPtr);
        std::cout << "Serialized uintptr_t value (hex): 0x" << std::hex << raw << std::dec 
                   << " (dec): " << raw << std::endl;

        // Deserialization
        Data* deserializedPtr = Serializer::deserialize(raw);
        std::cout << "Deserialized Pointer Address: " << deserializedPtr << std::endl;

        // Checks
        if (deserializedPtr == NULL)
            std::cout << "\n[SUCCESS] Deserialized NULL pointer remains NULL!" << std::endl;
        else
            std::cout << "\n[FAILURE] Deserialized pointer is not NULL!" << std::endl;
    }
    return 0;
}

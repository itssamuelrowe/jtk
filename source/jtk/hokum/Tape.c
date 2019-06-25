// Monday, May 27, 2019

#include <jtk/core/Float.h>
#include <jtk/core/Double.h>
#include <jtk/collection/array/Arrays.h>
#include <jtk/hokum/Tape.h>

/*******************************************************************************
 * Tape Flag                                                                   *
 *******************************************************************************/

bool jtk_TapeFlag_isExternalBuffer(uint32_t flags) {
    return (flags & JTK_TAPE_FLAG_EXTERNAL_BUFFER) != 0;
}

/*******************************************************************************
 * Tape                                                                        *
 *******************************************************************************/

// Constructor

jtk_Tape_t* jtk_Tape_wrap(uint8_t* value, int32_t size) {
    jtk_Tape_t* tape = jtk_Memory_allocate(jtk_Tape_t, 1);
    tape->m_value = value;
    tape->m_size = size;
    tape->m_index = 0;
    tape->m_flags = JTK_TAPE_FLAG_EXTERNAL_BUFFER;

    return tape;
}

// Destructor

void jtk_Tape_delete(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");

    if (!jtk_TapeFlag_isExternalBuffer(tape->m_flags)) {
        jtk_Memory_deallocate(tape->m_value);
    }
    jtk_Memory_deallocate(tape);
}

// Available

bool jtk_Tape_isAvailable(jtk_Tape_t* tape, int32_t required) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");

    return (tape->m_index + required) <= tape->m_size;
}

// Read

int8_t jtk_Tape_readUncheckedBoolean(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");

    return tape->m_value[tape->m_index++] != 0;
}

int8_t jtk_Tape_readUncheckedByte(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");

    return tape->m_value[tape->m_index++];
}

void jtk_Tape_readUncheckedBytes(jtk_Tape_t* tape, uint8_t* buffer, int32_t size) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + size) < tape->m_size, "No more bytes available.");

    jtk_Arrays_copyEx_b(tape->m_value, tape->m_size, tape->m_index, buffer,
        size, 0, size);
}

int16_t jtk_Tape_readUncheckedShort(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");

    return (int16_t)(((uint32_t)(tape->m_value[tape->m_index++] & 0xFF) << 8) |
        (tape->m_value[tape->m_index++] & 0xFF));
}

int32_t jtk_Tape_readUncheckedInteger(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");

    return ((tape->m_value[tape->m_index++] & 0xFF) << 24) |
        ((tape->m_value[tape->m_index++] & 0xFF) << 16) |
        ((tape->m_value[tape->m_index++] & 0xFF) << 8) |
        (tape->m_value[tape->m_index++] & 0xFF);
}

int64_t jtk_Tape_readUncheckedLong(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");

    return ((uint64_t)tape->m_value[tape->m_index++] << 56) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 48) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 40) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 32) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 24) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 16) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 8) |
           ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF));
}

float jtk_Tape_readUncheckedFloat(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");


    uint32_t bits = ((tape->m_value[tape->m_index++] & 0xFF) << 24) |
        ((tape->m_value[tape->m_index++] & 0xFF) << 16) |
        ((tape->m_value[tape->m_index++] & 0xFF) << 8) |
        (tape->m_value[tape->m_index++] & 0xFF);
    return jtk_Float_pack(bits);
}

double jtk_Tape_readUncheckedDouble(jtk_Tape_t* tape) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + 1) < tape->m_size, "No more bytes available.");
 
    uint64_t bits = ((uint64_t)tape->m_value[tape->m_index++] << 56) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 48) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 40) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 32) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 24) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 16) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF) << 8) |
                   ((uint64_t)(tape->m_value[tape->m_index++] & 0xFF));
    return jtk_Double_pack(bits);
}

void jtk_Tape_skipUnchecked(jtk_Tape_t* tape, int32_t count) {
    jtk_Assert_assertObject(tape, "The specified tape is null.");
    jtk_Assert_assertTrue((tape->m_index + count) < tape->m_size, "No more bytes available.");
    
    tape->m_index += count;
}
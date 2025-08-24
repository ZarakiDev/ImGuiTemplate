/* * * * * * * * * * * * * * * * * * *
 * * CGPMemory.h * * * * * * * * * * *
 * * CGuardProbe (And More!) * * * * *
 * * * * * * * * * * * * * * * * * * *
 * * Made by OPSphystech420  * * * * *
 * * Contributor ZarakiDev 2024 (c)  *
 * * * * * * * * * * * * * * * * * * */

#ifndef CGPMemory_h
#define CGPMemory_h

#include <mach-o/dyld.h>
#include <mach/mach.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/getsect.h>

#include <cstdio>
#include <algorithm>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <vector>
#include <memory>
#include <cctype>
#include <cstring>

#include "CGPError.h"

#include <libkern/OSCacheControl.h>

#define CGP_Type_ULong 8
#define CGP_Type_Double 8
#define CGP_Type_SLong 8
#define CGP_Type_Float 4
#define CGP_Type_UInt 4
#define CGP_Type_SInt 4
#define CGP_Type_UShort 2
#define CGP_Type_SShort 2
#define CGP_Type_UByte 1
#define CGP_Type_SByte 1

typedef struct _result_region {
    mach_vm_address_t region_base;
    std::vector<uint32_t> slide;
} ResultRegion;

typedef struct _result {
    std::vector< std::unique_ptr<ResultRegion> > resultBuffer;
    int count = 0;
} Result;

typedef struct _addr_range {
    uint64_t start;
    uint64_t end;
} AddrRange;

typedef struct _image_ptr {
    std::vector<uint64_t> base;
    std::vector<uint64_t> end;
} ImagePtr;

enum InstType
{
    ADRL,
    ADRP_LDR,
    ADRP_STR,
    LDR,
    STR
};

/* Instruction Decoder Class */
class CGPInstructionDecoder
{
public:
    bool DecodeADRImmediate(uint32_t insn, int64_t* imm) const;
    bool DecodeLDRSTRImmediate(uint32_t insn, int32_t* imm12) const;
    int32_t DecodeAddSubImmediate(uint32_t insn) const;

public:
    static int32_t GetBit(uint32_t insn, int pos);
    static int32_t GetBits(uint32_t insn, int pos, int length);

    static bool IsADR(uint32_t insn);
    static bool IsADRP(uint32_t insn);
    static bool IsLDR(uint32_t insn);
    static bool IsSTR(uint32_t insn);
    static bool IsBL(uint32_t insn);
    static bool IsLDRSTU(uint32_t insn);
    static bool IsLDRSTUImm(uint32_t insn);
    
    static bool IsFunctionRet(uint32_t insn);
    static size_t GetFunctionSize(void* funcAddr, size_t maxBytes = 1024 * 1024);
    
};

/* Memory Engine Class */
class CGPMemoryEngine : public CGPErrorHandler {
public:
    explicit CGPMemoryEngine(mach_port_t task);
    virtual ~CGPMemoryEngine();

private:
    /* Managed Data */
    void DeallocateResult();
    std::unique_ptr<Result> AllocateResult();

public:
    /* Memory Probe */
    void ScanMemory(const AddrRange& range, const void* target, size_t len);
    void NearBySearch(int range, const void* target, size_t len);
    bool SearchByAddress(uint64_t address, const void* target, size_t len);

    std::unique_ptr< std::vector<uint8_t> > ReadMemory(uint64_t address, size_t len) const;
    bool WriteMemory(uint64_t address, const void* data, size_t len);

    std::vector<void*> GetAllResults() const;
    std::vector<void*> GetResults(int count) const;

    void* AllocateMemory(size_t size);
    bool DeallocateMemory(void* address, size_t size);

    /* Memory Guard */
    kern_return_t ProtectMemory(void* address, size_t size, vm_prot_t protection);
    kern_return_t QueryMemory(void* address, vm_size_t* size, vm_prot_t* protection, vm_inherit_t* inheritance) const;

    bool isValid_;
    std::string error_;

protected:
    mach_port_t task_;
    std::unique_ptr<Result> result_;
    size_t pageSize_;
};

/* Memory Scanner Class */
class CGPMemoryScanner final : public CGPMemoryEngine, public CGPInstructionDecoder
{
public:
    CGPMemoryScanner(const std::string& binaryName, const std::string& segmentName = "__TEXT");
    ~CGPMemoryScanner() override = default;

public:
    /* Shortcuts for IDA Signitures */
    uintptr_t FindDirectSig(const std::string& signature, int step = 0) const;
    uintptr_t Find_ADRL_Sig(const std::string& signature, int step = 0) const;
    uintptr_t Find_ADRP_LDRSTR_Sig(const std::string& signature, int step = 0) const;
    uintptr_t Find_LDRSTR_Sig64(const std::string& signature, int step = 0) const;
    uintptr_t Find_LDRSTR_Sig32(const std::string& signature, int step = 0) const;
    
    template<typename FunctionType>
    inline __attribute__((always_inline))
    void InitializeFunction(FunctionType& Function, std::string const& Pattern)
    {
        Function = FunctionType(FindDirectSig(Pattern));
    }
    
    template<typename FunctionType>
    inline __attribute__((always_inline))
    void InitializeFunction(FunctionType& Function, void* Address)
    {
        Function = FunctionType(Address);
    }
    
    template<typename Type>
    inline __attribute__((always_inline))
    void InitializePointer(Type& Pointer, Type Address)
    {
        Pointer = Address;
    }
    
    template<typename PointerType>
    inline __attribute__((always_inline))
    void InitializePointer(PointerType*& Pointer, std::string const& Pattern, InstType Inst, int Step = 0)
    {
        switch (Inst)
        {
            case ADRL:
                Pointer = reinterpret_cast<PointerType*>(Find_ADRL_Sig(Pattern, Step));
                break;
            case ADRP_LDR:
            case ADRP_STR:
                Pointer = reinterpret_cast<PointerType*>(Find_ADRP_LDRSTR_Sig(Pattern, Step));
                break;
            default:
                Pointer = nullptr;
                break;
        }
    }

private:
    /* Scanner Utils */
    bool ComparePattern(const char* data, const char* pattern, const char* mask) const;
    uintptr_t SearchInRange(uintptr_t start, const char* pattern, const std::string& mask) const;
    uintptr_t GetPageOffset(uintptr_t address) const;

public:
    /* Byte Pattern */
    std::vector<uintptr_t> FindBytesAll(const std::vector<char>& bytes, const std::string& mask) const;
    uintptr_t FindBytesFirst(const std::vector<char>& bytes, const std::string& mask) const;

    /* IDA Pattern */
    std::vector<uintptr_t> FindIDAPatternAll(const std::string& pattern) const;
    uintptr_t FindIDAPatternFirst(const std::string& pattern) const;

public:
    /* Segment Data */
    uintptr_t SegmentStart_;
    uintptr_t SegmentEnd_;
};

#endif /* CGPMemory_h */

#include "tensorimpl.h"
#include "core.h"
#include "memory.h"
#include "math/math.h"
#include <string.h>

namespace tensor {

CoreTensorImpl::CoreTensorImpl(const std::string& name, const Dimension& dims)
        : TensorImpl(kCore, name, dims)
{
    data_ = memory::allocate<double>(numel());
    memset(data_,'\0', sizeof(double)*numel());
}
CoreTensorImpl::~CoreTensorImpl()
{
    if (data_) memory::free(data_);
}
void CoreTensorImpl::set_data(double* data, const IndexRange& range)
{
    if (range.size() == 0) {
        memcpy(data_,data,sizeof(double)*numel());
        return;
    }
    // TODO
}
void CoreTensorImpl::get_data(double* data, const IndexRange& range) const
{
    if (range.size() == 0) {
        memcpy(data,data_,sizeof(double)*numel());
        return;
    }
    // TODO
}
void CoreTensorImpl::zero()
{
    memset(data_,'\0', sizeof(double)*numel());
}
void CoreTensorImpl::scale(const double& a)
{
    VECTORIZED_LOOP
    for (size_t i=0, end=numel(); i<end; ++i) {
        data_[i] *= a;
    }
}
double CoreTensorImpl::norm(double power) const
{
    ThrowNotImplementedException;
}
double CoreTensorImpl::rms(double power) const
{
    ThrowNotImplementedException;
}
void CoreTensorImpl::scale_and_add(double a, ConstTensorImplPtr x)
{
    ThrowNotImplementedException;
}
void CoreTensorImpl::pointwise_multiplication(ConstTensorImplPtr x)
{
    ThrowNotImplementedException;
}
void CoreTensorImpl::pointwise_division(ConstTensorImplPtr x)
{
    ThrowNotImplementedException;
}
double CoreTensorImpl::dot(ConstTensorImplPtr x) const
{
    ThrowNotImplementedException;
}
void CoreTensorImpl::contract(ConstTensorImplPtr A, ConstTensorImplPtr B, const ContractionTopology &topology,
                              double alpha, double beta)
{

    CoreTensorContractionTopology manager(topology,*this,*(const CoreTensorImplPtr)A,*(const CoreTensorImplPtr)B);
    manager.contract(alpha,beta);
}
void CoreTensorImpl::permute(ConstTensorImplPtr A, const std::vector<int>& Ainds)
{
    // => Error Checks <= //

    /// Check rank(C) = rank(A)
    if (rank() != A->rank()) throw std::runtime_error("Tensors must be same rank");

    /// Check rank(Ainds) = rank(C) = rank(A)
    if (Ainds.size() != rank()) throw std::runtime_error("Ainds does not have correct rank");

    /// Check Ainds contains 0,1,2,...,rank-1
    std::vector<int> Ainds2 = Ainds;
    std::sort(Ainds2.begin(),Ainds2.end());
    for (int dim = 0; dim < rank(); dim++) {
        if (dim != Ainds2[dim])
            throw std::runtime_error("Ainds does not have dims 0,1,2,...");
    }

    /// Check size(C(i)) = size(A(Ainds(i))
    for (int dim = 0; dim < rank(); dim++) {
        if (dims()[dim] != A->dims()[Ainds[dim]])
            throw std::runtime_error("Permuted tensors do not have same dimensions");
    }

    // => Index Logic <= //

    /// Determine the number of united fast indices and memcpy size
    /// C_ij = A_ji would have no fast dimensions and a fast size of 1
    /// C_ijk = A_jik would have k as a fast dimension, and a fast size of dim(k)
    /// C_ijkl = A_jikl would have k and l as fast dimensions, and a fast size of dim(k) * dim(l)
    int fast_dims = 0;
    size_t fast_size = 1L;
    for (int dim = ((int)rank()) - 1; dim >= 0; dim++) {
        if (dim == Ainds[dim]) {
            fast_dims++;
            fast_size *= dims()[dim];
        } else {
            break;
        }
    }

    /// Determine the total number of memcpy operations
    int slow_dims = rank() - fast_dims;
    size_t slow_size = 1L;
    for (int dim = 0; dim < slow_dims; dim++) {
        slow_size *= dims()[dim];
    }

    /// Strides of slow indices of tensor A in its own ordering
    std::vector<size_t> Astrides(slow_dims,0L);
    if (slow_dims != 0) Astrides[slow_dims-1] = fast_size;
    for (int dim = slow_dims-2; dim >= 0; dim++) {
        Astrides[dim] = Astrides[dim+1] * A->dims()[dim];
    }

    /// Strides of slow indices of tensor A in the ordering of tensor C
    std::vector<size_t> AstridesC(slow_dims,0L);
    for (int dim = 0; dim < slow_dims; dim++) {
        AstridesC[dim] = Astrides[Ainds[dim]];
    }
    
    /// Strides of slow indices of tensor C in its own ordering
    std::vector<size_t> Cstrides(slow_dims,0L);
    if (slow_dims != 0) Cstrides[slow_dims-1] = fast_size;
    for (int dim = slow_dims-2; dim >= 0; dim++) {
        Cstrides[dim] = Cstrides[dim+1] * dims()[dim];
    }

    /// Handle to dimensions of C
    const std::vector<size_t>& Csizes = dims();
    
    /// Starting pointers
    double* Cp = data();
    double* Ap = ((const CoreTensorImplPtr)A)->data();

    // => Actual Permute Operation <= //

    if (slow_dims == 0) {
        // Fully sorted case or (equivalently) 0-rank tensors
        ::memcpy(Cp,Ap,sizeof(double)*fast_size);
    } else if (slow_dims == 1) {
        throw std::runtime_error("Should be topologically impossible to reach here.");
    } else if (slow_dims == 2) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}
    } else if (slow_dims == 3) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
        for (size_t Cind2 = 0L; Cind2 < Csizes[2]; Cind2++) {
            Atp += Cind2 * AstridesC[2];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}}
    } else if (slow_dims == 4) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
        for (size_t Cind2 = 0L; Cind2 < Csizes[2]; Cind2++) {
            Atp += Cind2 * AstridesC[2];
        for (size_t Cind3 = 0L; Cind3 < Csizes[3]; Cind3++) {
            Atp += Cind3 * AstridesC[3];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}}}
    } else if (slow_dims == 5) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
        for (size_t Cind2 = 0L; Cind2 < Csizes[2]; Cind2++) {
            Atp += Cind2 * AstridesC[2];
        for (size_t Cind3 = 0L; Cind3 < Csizes[3]; Cind3++) {
            Atp += Cind3 * AstridesC[3];
        for (size_t Cind4 = 0L; Cind4 < Csizes[4]; Cind4++) {
            Atp += Cind4 * AstridesC[4];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}}}}
    } else if (slow_dims == 6) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
        for (size_t Cind2 = 0L; Cind2 < Csizes[2]; Cind2++) {
            Atp += Cind2 * AstridesC[2];
        for (size_t Cind3 = 0L; Cind3 < Csizes[3]; Cind3++) {
            Atp += Cind3 * AstridesC[3];
        for (size_t Cind4 = 0L; Cind4 < Csizes[4]; Cind4++) {
            Atp += Cind4 * AstridesC[4];
        for (size_t Cind5 = 0L; Cind5 < Csizes[5]; Cind5++) {
            Atp += Cind5 * AstridesC[5];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}}}}}
    } else if (slow_dims == 7) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
        for (size_t Cind2 = 0L; Cind2 < Csizes[2]; Cind2++) {
            Atp += Cind2 * AstridesC[2];
        for (size_t Cind3 = 0L; Cind3 < Csizes[3]; Cind3++) {
            Atp += Cind3 * AstridesC[3];
        for (size_t Cind4 = 0L; Cind4 < Csizes[4]; Cind4++) {
            Atp += Cind4 * AstridesC[4];
        for (size_t Cind5 = 0L; Cind5 < Csizes[5]; Cind5++) {
            Atp += Cind5 * AstridesC[5];
        for (size_t Cind6 = 0L; Cind6 < Csizes[6]; Cind6++) {
            Atp += Cind6 * AstridesC[6];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}}}}}}
    } else if (slow_dims == 8) {
        #pragma omp parallel for
        for (size_t Cind0 = 0L; Cind0 < Csizes[0]; Cind0++) {
            double* Ctp = Cp + Cind0 * Cstrides[0]; 
            double* Atp = Ap + Cind0 * AstridesC[0];
        for (size_t Cind1 = 0L; Cind1 < Csizes[1]; Cind1++) {
            Atp += Cind1 * AstridesC[1];
        for (size_t Cind2 = 0L; Cind2 < Csizes[2]; Cind2++) {
            Atp += Cind2 * AstridesC[2];
        for (size_t Cind3 = 0L; Cind3 < Csizes[3]; Cind3++) {
            Atp += Cind3 * AstridesC[3];
        for (size_t Cind4 = 0L; Cind4 < Csizes[4]; Cind4++) {
            Atp += Cind4 * AstridesC[4];
        for (size_t Cind5 = 0L; Cind5 < Csizes[5]; Cind5++) {
            Atp += Cind5 * AstridesC[5];
        for (size_t Cind6 = 0L; Cind6 < Csizes[6]; Cind6++) {
            Atp += Cind6 * AstridesC[6];
        for (size_t Cind7 = 0L; Cind7 < Csizes[7]; Cind7++) {
            Atp += Cind7 * AstridesC[7];
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
            Ctp += fast_size;
        }}}}}}}}
    } else {
        for (size_t ind = 0L; ind < slow_size; ind++) {
            double* Ctp = Cp + ind * fast_size;
            double* Atp = Ap;
            size_t num = ind;
            size_t den = slow_size;
            for (int dim = 0; dim < slow_dims; dim++) {
                den /= AstridesC[dim];
                size_t offset = num / dim;
                Atp += offset * AstridesC[dim];
                num -= offset * den;
            } 
            ::memcpy(Ctp,Atp,sizeof(double)*fast_size);
        }
    }
}

std::map<std::string, TensorImplPtr> CoreTensorImpl::syev(EigenvalueOrder order) const
{
    ThrowNotImplementedException;
}
std::map<std::string, TensorImplPtr> CoreTensorImpl::geev(EigenvalueOrder order) const
{
    ThrowNotImplementedException;
}
std::map<std::string, TensorImplPtr> CoreTensorImpl::svd() const
{
    ThrowNotImplementedException;
}

TensorImplPtr CoreTensorImpl::cholesky() const
{
    ThrowNotImplementedException;
}

std::map<std::string, TensorImplPtr> CoreTensorImpl::lu() const
{
    ThrowNotImplementedException;
}
std::map<std::string, TensorImplPtr> CoreTensorImpl::qr() const
{
    ThrowNotImplementedException;
}

TensorImplPtr CoreTensorImpl::cholesky_inverse() const
{
    ThrowNotImplementedException;
}

TensorImplPtr CoreTensorImpl::inverse() const
{
    ThrowNotImplementedException;
}
TensorImplPtr CoreTensorImpl::power(double power, double condition) const
{
    ThrowNotImplementedException;
}

void CoreTensorImpl::givens(int dim, int i, int j, double s, double c)
{
    ThrowNotImplementedException;
}

CoreTensorContractionTopology::CoreTensorContractionTopology(
    const ContractionTopology& topology,
    const CoreTensorImpl& C,
    const CoreTensorImpl& A,
    const CoreTensorImpl& B) :
    topology_(topology),
    C_(C),
    A_(A),
    B_(B)
{
    std::vector<std::pair<int, std::string> > PC;
    std::vector<std::pair<int, std::string> > PA;
    std::vector<std::pair<int, std::string> > PB;
    std::vector<std::pair<int, std::string> > iA;
    std::vector<std::pair<int, std::string> > iC;
    std::vector<std::pair<int, std::string> > jB;
    std::vector<std::pair<int, std::string> > jC;
    std::vector<std::pair<int, std::string> > kA;
    std::vector<std::pair<int, std::string> > kB;

    const std::vector<std::string>& indices = topology_.indices();
    const std::vector<int>& A_pos = topology_.A_pos();
    const std::vector<int>& B_pos = topology_.B_pos();
    const std::vector<int>& C_pos = topology_.C_pos();
    const std::vector<ContractionType>& types = topology_.types();

    for (size_t ind = 0L; ind < indices.size(); ind++) {
        ContractionType type = types[ind];
        std::string tag = indices[ind];
        if (type == ABC) {
            PC.push_back(std::pair<int, std::string>(C_pos[ind],tag));
            PA.push_back(std::pair<int, std::string>(A_pos[ind],tag));
            PB.push_back(std::pair<int, std::string>(B_pos[ind],tag));
        } else if (type == AC) {
            iC.push_back(std::pair<int, std::string>(C_pos[ind],tag));
            iA.push_back(std::pair<int, std::string>(A_pos[ind],tag));
        } else if (type == BC) {
            jC.push_back(std::pair<int, std::string>(C_pos[ind],tag));
            jB.push_back(std::pair<int, std::string>(B_pos[ind],tag));
        } else if (type == AB) {
            kA.push_back(std::pair<int, std::string>(A_pos[ind],tag));
            kB.push_back(std::pair<int, std::string>(B_pos[ind],tag));
        }
    }

    std::sort(PC.begin(),PC.end());
    std::sort(PA.begin(),PA.end());
    std::sort(PB.begin(),PB.end());
    std::sort(iC.begin(),iC.end());
    std::sort(iA.begin(),iA.end());
    std::sort(jC.begin(),jC.end());
    std::sort(jB.begin(),jB.end());
    std::sort(kA.begin(),kA.end());
    std::sort(kB.begin(),kB.end());

    std::vector<std::string> compound_names;
    std::vector<std::vector<std::pair<int, std::string> > > compound_inds;

    compound_names.push_back("PC");
    compound_names.push_back("PA");
    compound_names.push_back("PB");
    compound_names.push_back("iC");
    compound_names.push_back("iA");
    compound_names.push_back("jC");
    compound_names.push_back("jB");
    compound_names.push_back("kA");
    compound_names.push_back("kB");

    compound_inds.push_back(PC);
    compound_inds.push_back(PA);
    compound_inds.push_back(PB);
    compound_inds.push_back(iC);
    compound_inds.push_back(iA);
    compound_inds.push_back(jC);
    compound_inds.push_back(jB);
    compound_inds.push_back(kA);
    compound_inds.push_back(kB);

    // Contiguous Index Test
    for (size_t ind = 0L; ind < compound_names.size(); ind++) {
        const std::vector<std::pair<int, std::string> >& compound_ind = compound_inds[ind];
        for (int prim = 0L; prim < ((int)compound_ind.size()) - 1; prim++) {
            if (compound_ind[prim+1].first != compound_ind[prim].first + 1) {
                throw std::runtime_error("Index is not contiguous:" + compound_names[ind]);
            }
        }
    }

    // Permutation Test
    for (size_t prim = 0L; prim < PC.size(); prim++) {
        if (PC[prim].second != PA[prim].second || PC[prim].second != PB[prim].second) {
            throw std::runtime_error("P indices are not all in same permutation");
        }
    }
    for (size_t prim = 0L; prim < iC.size(); prim++) {
        if (iC[prim].second != iA[prim].second) {
            throw std::runtime_error("i indices are not all in same permutation");
        }
    }
    for (size_t prim = 0L; prim < jC.size(); prim++) {
        if (jC[prim].second != jB[prim].second) {
            throw std::runtime_error("j indices are not all in same permutation");
        }
    }
    for (size_t prim = 0L; prim < kA.size(); prim++) {
        if (kA[prim].second != kB[prim].second) {
            throw std::runtime_error("k indices are not all in same permutation");
        }
    }

    // Hadamard Test
    int Psize = PC.size();
    if (Psize) {
        if (PC[0].first != 0) throw std::runtime_error("PC is not first index");
        if (PA[0].first != 0) throw std::runtime_error("PA is not first index");
        if (PB[0].first != 0) throw std::runtime_error("PB is not first index");
    }

    C_transpose_ = false;
    A_transpose_ = false;
    B_transpose_ = false;
    if (iC.size() && iC[0].first != Psize) C_transpose_ = true;
    if (iA.size() && iA[0].first != Psize) A_transpose_ = true;
    if (jB.size() && jB[0].first == Psize) B_transpose_ = true;

    ABC_size_ = 1L;
    AC_size_ = 1L;
    BC_size_ = 1L;
    AB_size_ = 1L;
    for (size_t prim = 0L; prim < PC.size(); prim++) {
        size_t size1 = C.dims()[PC[prim].first];
        size_t size2 = A.dims()[PA[prim].first];
        size_t size3 = B.dims()[PB[prim].first];
        if (size1 != size2 || size1 != size3)
            throw std::runtime_error("Hadamard indices are not same size");
        ABC_size_ *= size1;
    }
    for (size_t prim = 0L; prim < iC.size(); prim++) {
        size_t size1 = C.dims()[iC[prim].first];
        size_t size2 = A.dims()[iA[prim].first];
        if (size1 != size2)
            throw std::runtime_error("i indices are not same size");
        AC_size_ *= size1;
    }
    for (size_t prim = 0L; prim < jC.size(); prim++) {
        size_t size1 = C.dims()[jC[prim].first];
        size_t size2 = B.dims()[jB[prim].first];
        if (size1 != size2)
            throw std::runtime_error("j indices are not same size");
        BC_size_ *= size1;
    }
    for (size_t prim = 0L; prim < kA.size(); prim++) {
        size_t size1 = A.dims()[kA[prim].first];
        size_t size2 = B.dims()[kB[prim].first];
        if (size1 != size2)
            throw std::runtime_error("k indices are not same size");
        AB_size_ *= size1;
    }

}

void CoreTensorContractionTopology::contract(double alpha, double beta)
{
    double* Ap = A_.data();
    double* Bp = B_.data();
    double* Cp = C_.data();
    for (size_t P = 0L; P < ABC_size_; P++) {

        char transL;
        char transR;
        size_t nrow;
        size_t ncol;
        double* Lp;
        double* Rp;
        size_t ldaL;
        size_t ldaR;

        if (C_transpose_) {
            Lp = Bp;
            Rp = Ap;
            nrow = BC_size_;
            ncol = AC_size_;
            transL = (B_transpose_ ? 'N' : 'T');
            transR = (A_transpose_ ? 'N' : 'T');
            ldaL = (B_transpose_ ? AB_size_ : BC_size_);
            ldaR = (A_transpose_ ? AC_size_ : AB_size_);
        } else {
            Lp = Ap;
            Rp = Bp;
            nrow = AC_size_;
            ncol = BC_size_;
            transL = (A_transpose_ ? 'T' : 'N');
            transR = (B_transpose_ ? 'T' : 'N');
            ldaL = (A_transpose_ ? AC_size_ : AB_size_);
            ldaR = (B_transpose_ ? AB_size_ : BC_size_);
        }

        size_t nzip = AB_size_;
        size_t ldaC = (C_transpose_ ? AC_size_ : BC_size_);

        C_DGEMM(transL,transR,nrow,ncol,nzip,alpha,Lp,ldaL,Rp,ldaR,beta,Cp,ldaC);

        Cp += AC_size_ * BC_size_;
        Ap += AB_size_ * AC_size_;
        Bp += AB_size_ * BC_size_;
    }
}

}

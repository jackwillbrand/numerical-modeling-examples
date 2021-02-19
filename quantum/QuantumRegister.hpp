#include <vector>

template <int Q>
QuantumRegister<Q>::QuantumRegister(const MyVector<MyComplex<double>> &r)
{
    if(Q <= 0)
        throw std::invalid_argument("must have some qubits, otherwise useless");
    
    if(r.size() != std::pow(2, Q))
        throw std::invalid_argument("r wrong size for qubit register of given Q size");

    reg = r;
    measured_state = "";
    can_apply_gates = true;
}

template <int Q>
QuantumRegister<Q>::QuantumRegister(const QuantumRegister<Q> &src)
{
    reg = src.reg;
    measured_state = src.measured_state;
    can_apply_gates = src.can_apply_gates;
}

template <int Q>
void swap(const QuantumRegister<Q> &a, const QuantumRegister<Q> &b)
{
    swap(a.reg, b.reg);
    std::swap(a.measured_state, b.measured_state);
    std::swap(a.can_apply_gates, b.can_apply_gates);
}

template <int Q>
QuantumRegister<Q>& QuantumRegister<Q>::operator=(QuantumRegister<Q> qr)
{
    swap(*this, qr);
    return *this;
}

string to_binary(int num, int q)
{
    string result = "";

    for(int i = q - 1; i >= 0; i--)
    {
        int k = num >> i;
        if(k & 1)
            result.append("1");
        else
            result.append("0");
    }
    return result;
}

template <int Q>
string QuantumRegister<Q>::measure()
{
    if(measured_state != "")
        return measured_state;
    
    std::vector<double> prob;
    for(size_t i = 0; i < reg.size(); i++)
        prob.push_back((reg[i] * reg[i]).real());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<int> dd(std::begin(prob), std::end(prob));

    int chosen_index = dd(gen);
    measured_state = to_binary(chosen_index, Q);
    can_apply_gates = false;
    return measured_state;
}

template <int Q>
MyComplex<double> QuantumRegister<Q>::operator[](size_t index) const
{
    if(index < 0 || index >= reg.size())
        throw std::out_of_range("index out of range for quantum reg. access");
    return reg[index];
}

template <int Q>
void QuantumRegister<Q>::apply_gate(const QuantumGate &qg)
{
    if(qg.get_req_qubit_size() != Q)
        throw std::invalid_argument("qubit size incompat. with passed quantum gate");
    
    if(!can_apply_gates)
        throw std::invalid_argument("cannot apply gate to measured quantum register");
    
    MyComplex<double> old_zero = reg[0];
    MyComplex<double> old_one = reg[1];
    
    reg[0] = (old_zero * qg.get_gate()[0][0]) + (old_one * qg.get_gate()[1][0]);
    reg[1] = (old_zero * qg.get_gate()[0][1]) + (old_one * qg.get_gate()[1][1]);
}

template <int Q>
ostream& operator<<(ostream &out, QuantumRegister<Q> &qr)
{
    out << "Probabilities:";
    for(int i = 0; i < std::pow(2, Q); i++)
        out << " " << qr[i];
    out << std::endl << "Measured State: " << qr.measure();
    return out;
}
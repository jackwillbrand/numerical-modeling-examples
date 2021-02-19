HadamardGate::HadamardGate()
{
    MyComplex<double> sqrt2inv(1.0/std::sqrt(2.0), 0);
    MyComplex<double> neg_sqrt2inv(-1.0/std::sqrt(2.0), 0);

    gate = MyMatrix<MyComplex<double>>({{sqrt2inv, sqrt2inv}, {sqrt2inv, neg_sqrt2inv}});
    req_qubit_size = 1;
}

HadamardGate::HadamardGate(const HadamardGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
}

HadamardGate& HadamardGate::operator=(const HadamardGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
    return *this;
}

ostream& operator<<(ostream& out, const HadamardGate &hg)
{
    out << "Hadamard Gate:" << endl;
    out << hg.get_gate() << endl;
    return out;
}
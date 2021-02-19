PauliXGate::PauliXGate()
{
    MyComplex<double> zero(0, 0);
    MyComplex<double> one(1, 0);

    gate = MyMatrix<MyComplex<double>>({{zero, one}, {one, zero}});
    req_qubit_size = 1;
}

PauliXGate::PauliXGate(const PauliXGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
}

PauliXGate& PauliXGate::operator=(const PauliXGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
    return *this;
}

ostream& operator<<(ostream& out, const PauliXGate &hg)
{
    out << "PauliX Gate:" << endl;
    out << hg.get_gate() << endl;
    return out;
}
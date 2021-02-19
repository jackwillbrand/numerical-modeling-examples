PauliZGate::PauliZGate()
{
    MyComplex<double> zero(0, 0);
    MyComplex<double> one(1, 0);
    MyComplex<double> neg_one(-1, 0);

    gate = MyMatrix<MyComplex<double>>({{one, zero}, {zero, neg_one}});
    req_qubit_size = 1;
}

PauliZGate::PauliZGate(const PauliZGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
}

PauliZGate& PauliZGate::operator=(const PauliZGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
    return *this;
}

ostream& operator<<(ostream& out, const PauliZGate &hg)
{
    out << "PauliZ Gate:" << endl;
    out << hg.get_gate() << endl;
    return out;
}
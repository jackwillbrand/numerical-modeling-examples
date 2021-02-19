PhaseGate::PhaseGate()
{
    MyComplex<double> zero(0, 0);
    MyComplex<double> one(1, 0);
    MyComplex<double> i(0, 1);

    gate = MyMatrix<MyComplex<double>>({{one, zero}, {zero, i}});
    req_qubit_size = 1;
}

PhaseGate::PhaseGate(const PhaseGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
}

PhaseGate& PhaseGate::operator=(const PhaseGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
    return *this;
}

ostream& operator<<(ostream& out, const PhaseGate &hg)
{
    out << "Phase Gate:" << endl;
    out << hg.get_gate() << endl;
    return out;
}
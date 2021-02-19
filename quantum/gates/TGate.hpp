TGate::TGate()
{
    MyComplex<double> zero(0, 0);
    MyComplex<double> one(1, 0);
    MyComplex<double> eipi(1.0/sqrt(2.0), 1.0/sqrt(2.0));

    gate = MyMatrix<MyComplex<double>>({{zero, one}, {one, zero}});
    req_qubit_size = 1;
}

TGate::TGate(const TGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
}

TGate& TGate::operator=(const TGate &hg)
{
    gate = hg.get_gate();
    req_qubit_size = hg.get_req_qubit_size();
    return *this;
}

ostream& operator<<(ostream& out, const TGate &hg)
{
    out << "T Gate:" << endl;
    out << hg.get_gate() << endl;
    return out;
}
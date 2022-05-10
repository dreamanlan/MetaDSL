@@delimiter(script, "={:=", "=:}=");
namespace cv
{
	class CV_EXPORTS MinProblemSolver ":" public Algorithm
	{
		public ":";
		class CV_EXPORTS Function
		{
			public ":";
			virtual "~" Function()
			{
			};
			virtual int getDims()const "=" 0;
			virtual double getGradientEps()const;
			virtual double calc(const double "*" x)const "=" 0;
			virtual void getGradient(const double "*" x, double "*" grad);
		};
		virtual Ptr "<" Function ">" getFunction()const "=" 0;
		virtual void setFunction(const Ptr "<" Function ">" "&" f)"=" 0;
		virtual TermCriteria getTermCriteria()const "=" 0;
		virtual void setTermCriteria(const TermCriteria "&" termcrit)"=" 0;
		virtual double minimize(InputOutputArray x)"=" 0;
	};
	class CV_EXPORTS DownhillSolver ":" public MinProblemSolver
	{
		public ":";
		virtual void getInitStep(OutputArray step)const "=" 0;
		virtual void setInitStep(InputArray step)"=" 0;
		static Ptr "<" DownhillSolver ">" create(const Ptr "<" MinProblemSolver "::" Function ">" "&" f "=" Ptr "<" MinProblemSolver "::" Function ">"(), InputArray initStep "=" Mat_ "<" double ">"(1, 1, 0.0), TermCriteria termcrit "=" TermCriteria(TermCriteria "::" MAX_ITER "+" TermCriteria "::" EPS, 5000, 0.000001));
	};
	class CV_EXPORTS ConjGradSolver ":" public MinProblemSolver
	{
		public ":";
		static Ptr "<" ConjGradSolver ">" create(const Ptr "<" MinProblemSolver "::" Function ">" "&" f "=" Ptr "<" ConjGradSolver "::" Function ">"(), TermCriteria termcrit "=" TermCriteria(TermCriteria "::" MAX_ITER "+" TermCriteria "::" EPS, 5000, 0.000001));
	};
	enum SolveLPResult
	{
		SOLVELP_UNBOUNDED "=" "-" 2;
		SOLVELP_UNFEASIBLE "=" "-" 1;
		SOLVELP_SINGLE "=" 0;
		SOLVELP_MULTI "=" 1;
	};
	CV_EXPORTS_W int solveLP(const Mat "&" Func, const Mat "&" Constr, Mat "&" z);
};

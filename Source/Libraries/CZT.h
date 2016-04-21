/*
==============================================================================

CZT.h
Created: 8 Feb 2016 1:26:06pm
Author:  Chris

==============================================================================
*/

// ref: http://rosettacode.org/wiki/Fast_Fourier_transform#C.2B.2B

#ifndef CZT_H_INCLUDED
#define CZT_H_INCLUDED

#define CZT_32

#if defined(CZT_32)
typedef float fpt;
#elif defined(CZT_64)
typedef double fpt;
#endif

#define FPL(x) static_cast<fpt>(x)

#include <algorithm>
#include <cmath>
#include <complex>
#include <valarray>

const fpt PI = FPL(3.141592653589793238460);

typedef std::complex<fpt> cmplx;
typedef std::valarray<cmplx> cmplxarr;

/*
// Cooley–Tukey FFT (in-place)
inline void fft(cmplxarr& x)
{
	const size_t N = x.size();
	if (N <= 1) return;

	// divide
	cmplxarr even = x[std::slice(0, N / 2, 2)];
	cmplxarr odd = x[std::slice(1, N / 2, 2)];

	// conquer
	fft(even);
	fft(odd);

	// combine
	for (size_t k = 0; k < N / 2; ++k) {
		cmplx t = std::polar(FPL(1.0), FPL(-2.0) * PI * FPL(k) / FPL(N)) * odd[k];
		x[k] = even[k] + t;
		x[k + N / 2] = even[k] - t;
	}
}
*/

// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
// Better optimized but less intuitive
void fft(cmplxarr &x)
{
	// DFT
	unsigned int N = x.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	cmplx phiT = cmplx(cos(thetaT), sin(thetaT)), T;
	while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				cmplx t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			cmplx t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
	//// Normalize (This section make it not working correctly)
	//Complex f = 1.0 / sqrt(N);
	//for (unsigned int i = 0; i < N; i++)
	//	x[i] *= f;
}

// inverse fft (in-place)
inline void ifft(cmplxarr& x)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	fft(x);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= FPL(x.size());
}

// in place czt
// a = cmplx(1.0) for DFT
// w = std::exp(cmplx(0.0, FPL(-2.0) * PI / FPL(m))) for DFT
inline void czt(cmplxarr& x, int m, cmplx w, cmplx a) {
	// n = len(x)
	int n = x.size();

	// chirp = w ** (np.arange(1 - n, max(m, n)) ** 2 / 2.0)
	int maxmn = std::max(m, n);
	cmplxarr chirp(maxmn - (1 - n));
	for (int i = 0; i < chirp.size(); ++i) {
		cmplx ic = static_cast<cmplx>(i + (1 - n));
		chirp[i] = std::pow(w, FPL(0.5) * ic * ic);
	}

	// N2 = int(2 ** np.ceil(np.log2(m + n - 1)))  # next power of 2
	int n2 = static_cast<int>(std::pow(2.0, std::ceil(std::log2(m + n - 1))));

	// xp = np.append(x * a ** -np.arange(n) * chirp[n - 1 : n + n - 1], np.zeros(N2 - n))
	cmplxarr xp(n2);
	int i;
	for (i = 0; i < n; ++i) {
		xp[i] = x[i] * std::pow(a, -i) * chirp[n - 1 + i];
	}
	for (; i < n2; ++i) {
		xp[i] = cmplx(0.0);
	}

	// ichirpp = np.append(1 / chirp[: m + n - 1], np.zeros(N2 - (m + n - 1)))
	cmplxarr ichirpp(n2);
	for (i = 0; i < m + n - 1; ++i) {
		ichirpp[i] = cmplx(1.0) / chirp[i];
	}
	for (; i < n2; ++i) {
		ichirpp[i] = cmplx(0.0);
	}

	// r = np.fft.ifft(np.fft.fft(xp) * np.fft.fft(ichirpp))
	fft(xp);
	fft(ichirpp);
	cmplxarr r = xp * ichirpp;
	ifft(r);

	// return r[n - 1 : m + n - 1] * chirp[n - 1 : m + n - 1]
	x = r[std::slice(n - 1, m, 1)];
	x *= chirp[std::slice(n - 1, m, 1)];
};

// inverse fft (in-place)
inline void iczt(cmplxarr& x, int m, cmplx w, cmplx a)
{
	// conjugate the complex numbers
	x = x.apply(std::conj);

	// forward fft
	czt(x, m, w, a);

	// conjugate the complex numbers again
	x = x.apply(std::conj);

	// scale the numbers
	x /= FPL(x.size());
}

#endif  // CZT_H_INCLUDED
/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author(s)
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of turbinesFoam, which is based on OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::fv::turbineALSource

Description
    Abstract base class for turbine actuator line models.

SourceFiles
    turbineALSource.C

\*---------------------------------------------------------------------------*/

#ifndef turbineALSource_H
#define turbineALSource_H

#include "cellSetOption.H"
#include "volFields.H"
#include "OFstream.H"
#include "PtrList.H"
#include "actuatorLineSource.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{

/*---------------------------------------------------------------------------*\
                       Class turbineALSource Declaration
\*---------------------------------------------------------------------------*/

class turbineALSource
:
    public cellSetOption
{

protected:

    // Protected data

        //- Reference to time
        const Time& time_;

        //- Time value to track whether to move
        scalar lastRotationTime_;

        //- Reference density
        scalar rhoRef_;

        //- Angular velocity in radians/sec
        scalar omega_;

        //- Angle of turbine rotation in degrees
        scalar angleDeg_;

        //- Total number of turbine blades
        label nBlades_;

        //- Blade names
        wordList bladeNames_;

        //- Origin of turbine rotation
        vector origin_;

        //- Axis of turbine rotation
        vector axis_;

        //- Radial direction vector
        vector radialDirection_;

        //- Free stream velocity
        vector freeStreamVelocity_;

        //- Free stream direction
        vector freeStreamDirection_;

        //- Tip speed ratio
        scalar tipSpeedRatio_;

        //- Mean tip speed ratio
        scalar meanTSR_;

        //- TSR variation amplitude
        scalar tsrAmplitude_;

        //- TSR variation phase offset
        scalar tsrPhase_;

        //- Total rotor radius
        scalar rotorRadius_;

        //- Total force vector from turbine
        vector force_;

        //- Force field from turbine
        volVectorField forceField_;

        //- Total frontal area of turbine
        scalar frontalArea_;

        //- Power coefficient
        scalar powerCoefficient_;

        //- Drag coefficient
        scalar dragCoefficient_;

        //- Torque coefficient
        scalar torqueCoefficient_;

        //- Torque on turbine shaft
        scalar torque_;

        //- Dynamic stall subdictionary
        dictionary dynamicStallDict_;

        //- Subdictionary for individual blades
        dictionary bladesDict_;

        //- Subdictionary for element profile data
        dictionary profileData_;

        //- Moments from each blade
        List<vector> bladeMoments_;

        //- List of actuator line sources for blades
        PtrList<actuatorLineSource> blades_;

        //- Output file stream
        OFstream* outputFile_;


    // Protected Member Functions

        //- Rotate a 3D vector about a point and axis
        void rotateVector
        (
            vector& vectorToRotate,
            vector rotationPoint,
            vector axis,
            scalar radians
        );

        //- Create coordinate system
        virtual void createCoordinateSystem();

        //- Create actuator lines for blades
        virtual void createBlades();

        //- Create output file
        virtual void createOutputFile();

        //- Update tip speed ratio and rotational velocity
        void updateTSROmega();

        //- Rotate turbine a single time step based on omega
        virtual void rotate();

        //- Rotate turbine a specified angle about its axis
        virtual void rotate(scalar radians);

        //- Output performance summary to terminal
        virtual void printPerf();


public:

    //- Runtime type information
    TypeName("turbineALSource");


    // Constructors

        //- Construct from components
        turbineALSource
        (
            const word& name,
            const word& modelType,
            const dictionary& dict,
            const fvMesh& mesh
        );


    //- Destructor
    virtual ~turbineALSource();


    // Member Functions

        // Source term addition

            //- Add source term to momentum equation
            virtual void addSup
            (
                fvMatrix<vector>& eqn,
                const label fieldI
            );

            //- Add source term to compressible momentum equation
            virtual void addSup
            (
                const volScalarField& rho,
                fvMatrix<vector>& eqn,
                const label fieldI
            );

            //- Add source term to turbulence model equation
            virtual void addSup
            (
                fvMatrix<scalar>& eqn,
                const label fieldI
            );


        // I-O

            //- Read source dictionary
            virtual bool read(const dictionary& dict);

            //- Print dictionary values
            virtual void printCoeffs() const;

            //- Write performance to CSV
            virtual void writePerf();

            //- Write dictionary data
            virtual void writeData(Ostream& os) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                git branch: 'DEV', url: 'https://github.com/DouglasR99/traductor-backend.git'
            }
        }

        stage('Build') {
            steps {
                // Crear la carpeta bin si no existe
                bat 'if not exist bin mkdir bin'
                
                // Compilar todos los .cpp en ProyectoFinal
              bat 'g++ ProyectoFinal\\prototipoAVL\\main.cpp -o bin\\traductor.exe -lwinmm'

            }
        }

        stage('SonarQube Analysis') {
            environment {
                scannerHome = tool 'sonar-scanner'
            }
            steps {
                withSonarQubeEnv('sonarqube-local') {
                    bat "${scannerHome}\\bin\\sonar-scanner.bat -Dsonar.projectKey=traductor-backend -Dsonar.sources=ProyectoFinal\\prototipoAVL -Dsonar.language=cpp -Dsonar.login=squ_79195606cfbe4c76cbe0f91260ff331f36418b73"
                }
            }
        }
    }
}

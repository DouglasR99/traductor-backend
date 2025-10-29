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
                bat 'g++ ProyectoFinal\\*.cpp -o bin\\traductor.exe'
            }
        }

        stage('SonarQube Analysis') {
            environment {
                scannerHome = tool 'sonar-scanner'
            }
            steps {
                withSonarQubeEnv('sonarqube-local') {
                    bat "${scannerHome}\\bin\\sonar-scanner.bat -Dsonar.projectKey=traductor-backend -Dsonar.sources=ProyectoFinal"
                }
            }
        }
    }
}

-- MySQL Script generated by MySQL Workbench
-- Sun Mar 22 19:03:09 2020
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET utf8 ;
USE `mydb` ;

-- -----------------------------------------------------
-- Table `mydb`.`Owner`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Owner` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Owner` (
  `OwnerID` VARCHAR(45) NOT NULL,
  `OwnerName` VARCHAR(45) NOT NULL,
  `OwnerPhone` VARCHAR(25) NOT NULL,
  PRIMARY KEY (`OwnerID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Pet`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Pet` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Pet` (
  `PetID` INT NOT NULL,
  `PetName` VARCHAR(45) NOT NULL,
  `PetBreed` VARCHAR(45) NOT NULL,
  `ColorMarkings` VARCHAR(45) NOT NULL,
  `DOB` DATE NOT NULL,
  `Gender` VARCHAR(8) NOT NULL,
  `NeuteredSprayed` TINYINT NOT NULL,
  `Owner_OwnerID` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`PetID`),
  CONSTRAINT `fk_Pet_Owner`
    FOREIGN KEY (`Owner_OwnerID`)
    REFERENCES `mydb`.`Owner` (`OwnerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE INDEX `fk_Pet_Owner_idx` ON `mydb`.`Pet` (`Owner_OwnerID` ASC);


-- -----------------------------------------------------
-- Table `mydb`.`Trainers`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Trainers` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Trainers` (
  `TrainerID` INT NOT NULL,
  `TrainerName` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`TrainerID`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `mydb`.`Classes`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Classes` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Classes` (
  `ClassType` VARCHAR(45) NOT NULL,
  `Date` DATE NULL,
  `Time` TIME NULL,
  `Spcts` INT NULL,
  `Trainers_TrainerID` INT NOT NULL,
  PRIMARY KEY (`ClassType`, `Trainers_TrainerID`),
  CONSTRAINT `fk_Classes_Trainers1`
    FOREIGN KEY (`Trainers_TrainerID`)
    REFERENCES `mydb`.`Trainers` (`TrainerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE INDEX `fk_Classes_Trainers1_idx` ON `mydb`.`Classes` (`Trainers_TrainerID` ASC);


-- -----------------------------------------------------
-- Table `mydb`.`Event`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `mydb`.`Event` ;

CREATE TABLE IF NOT EXISTS `mydb`.`Event` (
  `PetID` INT NOT NULL,
  `SpecialCare` VARCHAR(45) NULL,
  `PetName` VARCHAR(45) NOT NULL,
  `Pet_PetID` INT NOT NULL,
  `Classes_ClassType` VARCHAR(45) NOT NULL,
  `Classes_Trainers_TrainerID` INT NOT NULL,
  PRIMARY KEY (`PetID`, `Pet_PetID`, `Classes_ClassType`, `Classes_Trainers_TrainerID`),
  CONSTRAINT `fk_TrainingForm_Pet1`
    FOREIGN KEY (`Pet_PetID`)
    REFERENCES `mydb`.`Pet` (`PetID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_TrainingForm_Classes1`
    FOREIGN KEY (`Classes_ClassType` , `Classes_Trainers_TrainerID`)
    REFERENCES `mydb`.`Classes` (`ClassType` , `Trainers_TrainerID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

CREATE INDEX `fk_TrainingForm_Pet1_idx` ON `mydb`.`Event` (`Pet_PetID` ASC) ;

CREATE INDEX `fk_TrainingForm_Classes1_idx` ON `mydb`.`Event` (`Classes_ClassType` ASC, `Classes_Trainers_TrainerID` ASC) ;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

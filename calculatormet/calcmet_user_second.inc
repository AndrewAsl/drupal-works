<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function calcmet_customer_form($form, &$form_state){
    $form = array();
    
    $cats = array(
        2 => t('Арматура'),
        3 => t('Двутавр'),
        4 => t('Квадрат'),
        5 => t('Полоса'),
        6 => t('Сталь'),
        7 => t('Труба'),
        8 => t('Швеллер'),
        9 => t('Шестигранник'),
        10 => t('Круглый прокат'),
    );    
    $form['choisecategory'][2] = array(
        '#type'  => 'button',
        '#value' => $cats[2],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][3] = array(
        '#type'  => 'button',
        '#value' => $cats[3],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][4] = array(
        '#type'  => 'submit',
        '#value' => $cats[4],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][5] = array(
        '#type'  => 'button',
        '#value' => $cats[5],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][6] = array(
        '#type'  => 'button',
        '#value' => $cats[6],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][7] = array(
        '#type'  => 'button',
        '#value' => $cats[7],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][8] = array(
        '#type'  => 'button',
        '#value' => $cats[8],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][9] = array(
        '#type'  => 'button',
        '#value' => $cats[9],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    $form['choisecategory'][10] = array(
        '#type'  => 'button',
        '#value' => $cats[10],
        '#ajax' => array(
            'callback' => 'calcmet_choise',
            'wrapper' => 'calculatedzone',
        ),
    );
    
    $form['calculatedzone'] = array(
        '#type' =>  'fieldset',
        '#prefix' => '<div id = "calculatedzone">',
        '#suffix' => '</div>'    
    );    
    
    return $form;
}
function _tube_change_calculator_type($form, $form_state){
    
    //$commands[] = ajax_command_replace("#calculator-type-zone", "<div id='#calculator-type-zone'>$form</div>" );
    dpm($form_state['values']);
    return $form['calculatedzone']['tubename'];
}

function calcmet_customer_form_tube($form, &$form_state){
    $form = array();
    $form['calculatedzone'] = array(
        '#title' => t('Трубы'),
        '#type' =>  'fieldset',
        '#prefix' => '<div id = "calculatedzone">',
        '#suffix' => '</div>'    
    );    
    $form['calculatedzone']['tubeundercategory'] = array(
        '#type' =>  'select',
        '#options' => _get_undercategory_options(7),
        //'#ajax' => array(
        //    'callback' => '_tube_change_calculator_type',
        //    'wrapper' => 'calculator-type-zone',
        //),
        //'#suffix' => '<div id="calculator-type-zone"></div>',
        //'#action' =>  url('services/calcmet'),
    );
    $form['calculatedzone']['submit'] = array(
       '#type' =>  'submit',
        '#value' => 'отправить',
       '#submit' => array('_tube_change_calculator_type'),
    );
    $form['calculatedzone']['picture'] = array(
        '#type' =>  'item',
        '#markup' => '<div><img src="#" width="200" height="200"></div>'    
    );
    /*$form['calculatedzone']['calculator'] = array(
        '#type' =>  'item',
        '#markup' => '<div id="calculator-type-zone"></div>'
    );*/
    $selectcat = isset($form_state['values']['tubeundercategory'])? $form_state['values']['tubeundercategory'] : 0;
    dsm($selectcat);
    $form['calculatedzone']['tubename'] = array(
        '#prefix' => '<div id="calculator-type-zone">',
        '#title' => 'Труба',
        '#type' => 'select',
        '#size' => 10,
        '#options' => _get_tube_name_for_options($selectcat),
        '#ajax' => array (
            'callback' => '',
            'wrapper' => '',
        ),
    );
    $form['calculatedzone']['lenght'] = array(
        '#title' => 'Длина, м',
        '#type' => 'textfield',
        '#size' => 30,
        '#ajax' => array(
            'callback' => '',
            'wrapper' => '',
        ),
        '#suffix' => '</div>',
    );
    return $form;
}

function calcmet_choise($form, $form_state){
    $name = $form_state['values']['op'];
    //dsm ($name);
    switch ($name) {
        case t('Арматура'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Двутавр'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Квадрат'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Полоса'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Сталь'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Труба'):
            $form = render(drupal_get_form('calcmet_customer_form_tube'));
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$form</div>" );
            break;
        case t('Швеллер'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Шестигранник'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        case t('Круглый прокат'):
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>$name</div>" );
            break;
        default:
            $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>Арматура</div>" );
            break;
    }
    return array('#type' => 'ajax', '#commands' => $commands);
}
/*
function calcmet_customer_form_submit($form, $form_state){
    dsm ($form_state);
    //$name = $form_state['values']['name'];
    $commands[] = ajax_command_replace("#calculatedzone", "<div id='calculatedzone'>Hello</div>" );
    drupal_set_message('hello');
    return array('#type' => 'ajax', '#commands' => $commands);
}*/
function _get_undercategory_options($cat){
    $entries = db_select('calcmetundercat', 'uc')
            -> fields('uc')
            -> condition ('uc.ccid', $cat)
            -> execute()
            -> fetchAll();
    //dsm($entries);
    foreach ($entries as $entry) {
      $options[$entry->cucid] = $entry->title;
    }
    if (isset($options)) {
        return $options;
    }
    else {
        return array('В данной категории подразделы отсуствуют');
    }
}


function _get_tube_name_for_options ($case){
    dsm($case);
    switch ($case) {
        case 5:
            $basename = 'calcmettubessteelwithoutseam';
            break;
        case 6:
            $basename = 'calcmettubestellsvarnpryamoshovn';
            break;
        default:
            $basename = 'calcmettubestellsvarnpryamoshovn';
            break;
    }
    $entries = db_select($basename)
            -> fields($basename)
            -> execute()
            -> fetchAll();
    dsm($entries);
    foreach ($entries as $entry) {
      if ($basename == 'calcmettubestellsvarnpryamoshovn'){  
        $options[$entry->tsshdid] = $entry->tsshname;
      }
    }
    //if (isset($options)) {
        return $options;
    //}
}